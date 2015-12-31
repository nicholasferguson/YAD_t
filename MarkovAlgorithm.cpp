#include "MarkovAlgorithm.h"
#include "wc2rx.h"
#include <algorithm>
#include <string>
#include <regex>
#include <iterator>
#include <iostream>

MarkovAlgorithm::MarkovAlgorithm(MarkovAlphabet alphabet,
                                 std::vector<MarkovRule> rules,
                                 MarkovAlphabet input_alphabet)
    : _alphabet(alphabet),
      _rules(rules),
      _input_alphabet(input_alphabet)
{

}

bool MarkovAlgorithm::RuleFitResult::isValid() const
{
    return start_index >= 0 && length >= 0;
}

MarkovAlgorithm::RuleFitResult::RuleFitResult(
        int start_index_,
        int length_)
    : start_index(start_index_),
      length(length_)
{}

MarkovAlgorithm::RuleFitResult MarkovAlgorithm::isRuleFits(
        std::string input_word, const MarkovRule& rule, bool isEscaping)
{
    std::string pattern = rule.getLeftPart();
	std::string pattern_empty;
	// replace $ by a blank.  It will not be used as a regex symbol. YAD syntactic sugar....
	// When  '$' is removed and edited text goes into pattern_empty.
	// pattern_empty will be blank...And gets handled by code block below. 
	// to return RuleFitResult(0, 0);  This will be the ONLY rule handled by block below.
	std::remove_copy(pattern.begin(), pattern.end(), std::back_inserter(pattern_empty), '$');

    //Empty string matches the beginning.  This is $
	if (pattern_empty.length() == 0 ){
		return RuleFitResult(0, 0);

	}
	// This is code added for regex engine.  But in fact... this code does not
	// use any symbols as regex symbols.... but the regex engine is good to have at this stage.
	// Commands to this regex engine is transformed by a function wc2rx. See wc2rx.cpp
	std::smatch m;
	std::regex ex(wc2rx(pattern_empty, false,isEscaping));
	bool matched = std::regex_search(input_word, m, ex);
	int index = -1;
	// rule has a match in input_word.
	if (matched == true)
		index = m.prefix().length();
	else
		index = -1;
	if (index < 0)
        return RuleFitResult(-1, -1);   // no match
    return RuleFitResult(index, pattern_empty.length()); // match.
}
std::string MarkovAlgorithm::useRule(std::string input_word,
                               MarkovRule& rule, bool isEscaping)
{
    std::string res="";
    RuleFitResult rule_fits = isRuleFits(input_word,rule, isEscaping);
    rule_fits.start_index;
	res = input_word.substr(0, rule_fits.start_index);
    res+= rule.getRightPart();
	res += input_word.substr(rule_fits.start_index + rule_fits.length,
		input_word.size());
    return res;
}

const MarkovRule* MarkovAlgorithm::getRuleFor(std::string input, bool isEscaping) const
{
    const MarkovRule* res = nullptr;

    for(int i=0; i<_rules.size(); ++i)
    {
        RuleFitResult fit = isRuleFits(input, _rules[i],isEscaping);

        if(fit.isValid())
        {
            res = &_rules[i];
			//if(OUTPUT) std::cout << "Rule # " << i << std::endl;
            break;
        }
    }


    return res;
}
const MarkovAlphabet& MarkovAlgorithm::getInputAlphabet() const
{
    return _input_alphabet;
}
const MarkovAlphabet& MarkovAlgorithm::getAlphabet() const
{
    return _alphabet;
}

std::vector<MarkovRule> MarkovAlgorithm::getRules() const
{
    return _rules;
}
