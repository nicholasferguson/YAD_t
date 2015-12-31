
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <stdarg.h>
#include "MarkovRunManager.h"
#include  <boost/format.hpp>


MarkovRunManager* MarkovRunManager::_instance = nullptr;



MarkovRunManager* MarkovRunManager::getInstance( )
{
    if (_instance == nullptr)
        _instance = new MarkovRunManager();
    return _instance;
}

MarkovRunManager::MarkovRunManager():
    _input_word(""),
    _steps_made(0),
    _word_after_last_step(""),
    _is_debug_mode(false),
    _stop_on_next_step(false),
    _terminate_on_next_step(false)
{
}

RunError notInAlphabet(std::string letter, MarkovAlphabet alphabet_m, std::string name="T")
{
    std::string old_alphabet(letter);
    old_alphabet += ", " + alphabet_m.getSource();

	std::stringstream ss;  ss.clear();
	ss << "Symbol ' " << letter <<" ' is not in alphabet";
	std::string title = ss.str();
	ss.clear();
	ss << "You can add it to alphabet. Examples: '" << name << "= {" << old_alphabet << "}'.";
	std::string description = ss.str();


    return RunError(title, description, 305);
}

int MarkovRunManager::getStepNumberOfValue(std::string word)
{

    std::set<StepResult>::iterator it = std::find(_steps_history.begin(),
                                          _steps_history.end(),
                                          StepResult(word,0));
    if (it != _steps_history.end())
        return (*it)._step_id;
    return -1;
}
bool MarkovRunManager::choseAndUseRule(std::string& word,
                                       MarkovRule& rule, bool isEscaping)
{
    //get rule
    const MarkovRule*  markov_rule = _algorithm.getRuleFor(word, isEscaping);
    std::string res="";

    //use rule
    if(markov_rule != nullptr)
    {
        rule = *markov_rule;

        res = _algorithm.useRule(word,rule, isEscaping);
        word = res;
        return true;
    }
    return false;
}

bool MarkovRunManager::findAndApplyNextRule(bool isEscaping)
{
	std::string startWord = _word_after_last_step;
    if(_terminate_on_next_step)
    {
        _terminate_on_next_step = false;

        return false;
    }
	
    if(_word_after_last_step.size()>2000)
    {
		std::stringstream ss;ss.clear();
		ss << "Result can not be longer than 2000 symbols. On step #" << _steps_made << " input become " << _word_after_last_step.size() << " symbols long";
		std::string description = ss.str();
		RunError error("Too long result",description,101);
        return false;
    }

    //Go through MarkovRules and select which fits.
    //If there are no rules then emit debugFinishSuccess or
    //runWithoutDebugFinishSuccess depending on run mode.
    //Use as _word_after_last_step as output word.

    std::string word = _word_after_last_step;
    MarkovRule rule;
    if(!choseAndUseRule(word, rule, isEscaping))
    {

        return false;
    }

    ++_steps_made;


    _word_after_last_step = word;

	
	if (_steps_history.find(StepResult(_word_after_last_step, 0)) != _steps_history.end())
    {
        std::string last_step = _word_after_last_step;
        if(last_step.size() > 30)
            last_step = last_step.substr(0, 30) + "...";

        int prev_same_stem = getStepNumberOfValue(_word_after_last_step);

		boost::format f("The result of step #%1% is same as on the step #%2%\n('%3%')");
		f % prev_same_stem; f % _steps_made;f % last_step;
		std::string description = f.str();
        RunError error("Algorithm never terminates", description, 102);


        return false;
    }

    _steps_history.insert(StepResult(_word_after_last_step,_steps_made));




    //If rule is final then emit debugFinishSuccess or
    //runWithoutDebugFinishSuccess depending on run mode.
    //Use as _word_after_last_step as output word. return false.

    if(rule.isFinalRule())
    {
        
        return false;
    }
	if(OUTPUT) std::cout << "Step # " << _steps_made << std::endl;
	if(OUTPUT) std::cout << "Rule: " << rule.getLeftPart() << " -> " << rule.getRightPart() << std::endl;
	if(OUTPUT) std::cout << "Before: " << startWord << std::endl;
	if(OUTPUT) std::cout << "After: " << _word_after_last_step << std::endl << std::endl;

    return true;
}

void MarkovRunManager::setAlgorithm(MarkovAlgorithm algorithm)
{
    _algorithm = algorithm;
}

void MarkovRunManager::setCanRunSourceCode(bool can)
{

}

bool hasSymbolsNotInAlphabet(std::string input_word,
                             MarkovAlphabet alphabet,
                             char& symbol)
{
    for(int i=0; i<input_word.size(); ++i)
    {
        char ch = input_word[i];
        if(!alphabet.isInAlphabet(ch))
        {
            symbol = ch;
            return true;
        }
    }
    return false;
}

void MarkovRunManager::runWithoutDebug(std::string input_word, bool isEscaping)
{
    _stop_on_next_step = false;
    _terminate_on_next_step = false;
    _steps_made = 0;
    _steps_history.clear();
    _input_word = input_word;
    _word_after_last_step = input_word;
    _is_debug_mode = false;


    if(isInputValid(input_word))
    {


        while(findAndApplyNextRule(isEscaping))
        {
        }
    }
}
bool MarkovRunManager::isInputValid(std::string input_word)
{
    char test;
    if(_algorithm.getInputAlphabet().isAuto())
    {
        if(hasSymbolsNotInAlphabet(input_word,
                                   _algorithm.getAlphabet(),
                                   test))
        {
          
            return false;
        }
    }
    else
    {
        if(hasSymbolsNotInAlphabet(input_word,
                                   _algorithm.getInputAlphabet(),
                                   test))
        {
            return false;
        }
    }


    return true;
}

void MarkovRunManager::doStartDebug(std::string input_word, bool stop_at_first_step, bool isEscaping)
{
    _stop_on_next_step = stop_at_first_step;
    _terminate_on_next_step = false;
    _steps_made = 0;
    _steps_history.clear();
    _input_word = input_word;
    _word_after_last_step = input_word;
    _is_debug_mode = true;

    if(isInputValid(input_word))
    {
        while(findAndApplyNextRule(isEscaping))
        {   }
    }
}

void MarkovRunManager::runWithDebug(std::string input_word, bool isEscaping)
{
    doStartDebug(input_word, false, isEscaping);
}

void MarkovRunManager::runWithDebugStepByStep(std::string input_word, bool isEscaping)
{
    doStartDebug(input_word, true, isEscaping);
}

void MarkovRunManager::addBreakPoint(int line_number)
{
    _break_points.insert(line_number);
}

void MarkovRunManager::removeBreakPoint(int line_number)
{
    _break_points.erase(line_number);
}

void MarkovRunManager::debugNextStep(bool isEscaping)
{
    _stop_on_next_step = true;
	findAndApplyNextRule(isEscaping);
}

void MarkovRunManager::debugContinue(bool isEscaping)
{
	while (findAndApplyNextRule(isEscaping))
    {

    }
}
void MarkovRunManager::terminateRun()
{
    _terminate_on_next_step = true;
}

void MarkovRunManager::debugStop()
{
   
}
bool operator<(const StepResult& a, const StepResult& b)
{
    return a._output < b._output;
}
bool operator==(const StepResult& a, const StepResult& b)
{
    return a._output == b._output;
}
