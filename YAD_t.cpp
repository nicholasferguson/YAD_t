// YAD_t.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "MarkovRule.h"
#include "MarkovAlgorithm.h"
#include "YadFile.h"
#include "MarkovParser.h"
#include "MarkovRunManager.h"

std::string CompareTestResults(std::string filename, std::string input)
{

	if (filename == "Rosetta.ruleset1.yad" && input == "I bought a B of As from T S.")
		return "I bought a bag of apples from my brother.";
	else if (filename == "Rosetta.ruleset2.yad" && input == "I bought a B of As from T S.")
		return "I bought a bag of apples from T shop.";
	else if (filename == "Rosetta.ruleset3.yad" && input == "I bought a B of As W my Bgage from T S.")
		return "I bought a bag of apples with my money from T shop.";
	else if (filename == "Rosetta.ruleset4.yad" && input == "I bought a B of As from T S.")
		return "11111111111111111111";
	else if (filename == "Rosetta.ruleset5.yad" && input == "I bought a B of As from T S.")
		return "00011H1111000";
	else if (filename == "YAD.Studo.multiply.yad" && input == " |||#|| ")
		return "||||||";
	else if (filename == "YAD.Studo.mirrow.yad" && input == "cabbbbaaaabbbbaabbcccccc")
		return "ccccccbbaabbbbaaaabbbbac";
	else return "test not documented";


}

void debugWikiMarkovAlgo1()
{
	// 1. ========== setup objects for running Markov Algorithm
	MarkovAlphabet alphabet = MarkovAlphabet();
	MarkovAlphabet input_alphabet = MarkovAlphabet(true);
	std::vector<MarkovRule> rules;
	rules.push_back(MarkovRule("A", "apple"));
	rules.push_back(MarkovRule("B", "bag"));
	rules.push_back(MarkovRule("S", "shop"));
	rules.push_back(MarkovRule("T", "the"));
	rules.push_back(MarkovRule("the shop", "my brother"));
	MarkovAlgorithm algo(alphabet, rules, input_alphabet);

	// 2. ========== input to transform
	std::string before_rule_applied = "I bought a B of As from T S.";

	if(OUTPUT) std::cout << "Input_string before it is transformed: " << before_rule_applied << std::endl;

	// 3. ========== Run Markov Algorithm
	if (OUTPUT)  std::cout << "Output from running algorithm" << std::endl;
	MarkovRunManager* run_manager = MarkovRunManager::getInstance();
	run_manager->setAlgorithm(algo);
	run_manager->runWithDebug(before_rule_applied, false);

	// 4. ==========Output transformed input.
	if(OUTPUT) std::cout << "Final string output from running algorithm: " << run_manager->_word_after_last_step << std::endl;


}
/* debugWikiMarkovAlgo2
rewrite binary numbers to their unary counterparts
it will terminate after the following steps.
1."101"
2."0|01"
3."00||1"
4."00||0|"
5."00|0|||"
6."000|||||"
7."00|||||"
8."0|||||"
9."|||||"

*/
void debugWikiMarkovAlgo2()
{
	// 1. ========== setup objects for running Markov Algorithm
	MarkovAlphabet alphabet = MarkovAlphabet();
	MarkovAlphabet input_alphabet = MarkovAlphabet(true);
	std::vector<MarkovRule> rules;
	rules.push_back(MarkovRule("|0", "0||"));
	rules.push_back(MarkovRule("1", "0|"));
	rules.push_back(MarkovRule("0" , ""));
	MarkovAlgorithm _algorithm(alphabet, rules, input_alphabet);

	// 2. ========== input to transform
	std::string before_rule_applied = "101";

	if(OUTPUT)  std::cout << "Input_string before it is transformed: " << before_rule_applied << std::endl;

	// 3. ========== Run Markov Algorithm
	if (OUTPUT)  std::cout << "Output from running algorithm" << std::endl;
	MarkovRunManager* run_manager = MarkovRunManager::getInstance();
	run_manager->setAlgorithm(_algorithm);
	run_manager->runWithDebug(before_rule_applied, false);

	// 4. ==========Output transformed input.
	if(OUTPUT) std::cout << "Final string output from running algorithm: : " << run_manager->_word_after_last_step << std::endl;


}
void debugMarkovAlgo3(std::string file_name, std::string input_string)
{
	// 1. ========== setup objects for running Markov Algorithm
	// 1.0. ========== read in file 
	YadFile file = YadFile::readFromFile(file_name);

	// 1.1. ========== set up some objects for Markov Algorithm
	std::vector<CompilerError> _errors;
	MarkovAlgorithm alg;

	// 1.2. ========== get info from file
	std::string source_code = file.getSourceCode();

	// 1.3. ========== parse into Markov Algorithm
	bool res = MarkovParser::parseSourceCode(source_code, alg, _errors);

	// 2. ========== Print out input_string before it is transformed.
	std::string  before_rule_applied(input_string); 
	if (OUTPUT)  std::cout << std::endl;
	if (OUTPUT)  std::cout << "Input_string before it is transformed: " << before_rule_applied << std::endl << std::endl;

	// 3. ========== Run Markov Algorithm
	if (OUTPUT)  std::cout << "Output from running algorithm:" << std::endl;
	MarkovRunManager* run_manager = MarkovRunManager::getInstance();
	run_manager->setAlgorithm(alg);
	run_manager->runWithDebug(before_rule_applied,true);

	// 4. ========== Print out transformed input.
	if(OUTPUT)  std::cout << "Final string output from running algorithm: " <<  run_manager->_word_after_last_step << std::endl;


}
int main(int argc, char* argv[])
{


	debugWikiMarkovAlgo1(); // do replacements
    debugWikiMarkovAlgo2(); // turn binary into a count of sticks. 101 = five sticks |||||
    debugMarkovAlgo3("YAD.Studo.multiply.yad", std::string("|||#||")); // 3*2 = 6
	debugMarkovAlgo3("YAD.Studo.mirrow.yad",std::string("cabbbbaaaabbbbaabbcccccc"));  // reverse this string.
	debugMarkovAlgo3("Rosetta.ruleset1.yad", std::string("I bought a B of As from T S"));  // reverse this string.
	debugMarkovAlgo3("Rosetta.ruleset2.yad", std::string("I bought a B of As from T S"));  // reverse this string.
	debugMarkovAlgo3("Rosetta.ruleset3.yad", std::string("I bought a B of As W my Bgage from T S"));  // reverse this string.
	debugMarkovAlgo3("Rosetta.ruleset4.yad", std::string("_1111*11111_"));  // reverse this string.
	debugMarkovAlgo3("Rosetta.ruleset5.yad", std::string("000000A000000"));  // reverse this string.
	return 0;
}
/*
notes on multiply.yad
one rule $ -> S* will fit any token, because $ is replace by '', empty set.  And empty set is a subset of all subsets.
therefore in multiply.yad, this rule is the last rule.
When a token needs a rule, there are 12 of them.  for loop starts at 0, until it finds correct rule.
rule $ -> S* is the first rule matched... But that rule should never be reached again, otherwise it creates a non ending loop.

this engine is not using regex symbols, like ^ $...etc... instead it is using char replacements.
*/

