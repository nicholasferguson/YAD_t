#include "MarkovParser.h"
#include "MarkovAlgorithm.h"
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>
#include <boost/spirit/include/qi.hpp>

namespace Parser
{
	static std::string forbidden_symbols(">-. TI={}");
}
using namespace Parser;

std::string removeComments(std::string line)
{
	int comments_index = line.find("//");
	if (comments_index >= 0)
		return line.substr(0, comments_index);
	return line;
}

std::string trim(std::string line)
{
	boost::algorithm::trim(line);
	return line;
}

CompilerError wrongAlphabetChar(int line, std::string letter)
{
	std::stringstream s; s.clear(); s.str(""); s << "Symbol '" + letter + "' can't be used in alphabet";
	std::string title = s.str();
	std::string description("In alphabet can be used only characters. Examples: 'T = {a, b, c, d}'.");

	return CompilerError(title, description, 201, line);
}

CompilerError charAlreadyInAlphabet(int line, std::string letter)
{
	std::stringstream s; s.clear(); s.str(""); s << "Symbol '" << letter << "' can't be used in alphabet";
	std::string title = s.str();
	std::string description("In alphabet can be used only characters. Examples: 'T = {a, b, c, d}'.");
	return CompilerError(title, description, 204, line);
}

CompilerError emptySymbolInAlphabet(int line)
{
	std::string title("Symbol '$' can't be added to alphabet");
	std::string description("'$' means an empty symbol and is already a part of alphabet.");

	return CompilerError(title, description, 201, line);
}

CompilerError forbiddenInAlphabet(int line, std::string letter)
{
	std::stringstream s; s.clear(); s.str(""); s << "Symbol '" << letter << "' can't be used in alphabet";
	std::string title = s.str();
	std::string description("You can use any other symbol. Examples: 'T = {a, b, c, d}'.");

	return CompilerError(title, description, 205, line);
}

CompilerError notInAlphabet(int line, std::string letter, MarkovAlphabet alphabet)
{

	std::stringstream s; s.clear(); s.str(""); s << "Symbol '" << letter << "' is not in alphabet";
	std::string title = s.str(); s.clear();
	s << "You can add it to alphabet. Examples: 'T {" << letter << "," << alphabet.getSource() << "'.";
	std::string description = s.str();
	return CompilerError(title, description, 200, line);
}

CompilerError forbiddenInRule(int line, std::string letter)
{
	std::stringstream s; s.clear(); s.str(""); s << "Symbol '" << letter << "'";
	std::string title = s.str();
	std::string description("You can use any other symbol which are in alphabet.");
	return CompilerError(title, description, 200, line);
}

CompilerError wrongRuleDefenition(int line, std::string text)
{
	std::string title("Wrong rule definition");
	std::stringstream s; s.clear(); s.str(""); s << "Definition of rule is wrong. ('" << text << "') Example: 'aa -> bb' or 'aa ->. bb'";
	std::string description = s.str();
	return CompilerError(title, description, 203, line);
}

CompilerError noAlphabetDefenition(int line)
{
	std::string title = ("Alphabet definition is not found");
	std::string description("Alphabet definition example: 'T = {a,b,c}'");

	return CompilerError(title, description, 202, line);
}

bool isCharsInAlphabet(int line_number, std::string text,
	std::vector<CompilerError>& errors,
	MarkovAlphabet& alphabet)
{
	std::replace(text.begin(), text.end(), '$', ' ');

	bool res = true;
	for (size_t i = 0; i <text.length(); ++i)
	{
		char ch = text[i];
		if (!alphabet.isInAlphabet(ch))
		{
			if (forbidden_symbols.find(ch) >= 0)
				errors.push_back(forbiddenInRule(line_number, std::to_string(ch)));
			else{
				errors.push_back(notInAlphabet(line_number, std::to_string(ch), alphabet));

			res = false;
			}
			break;
		}
	}
	return res;
}

void parseRule(int line_number, std::string line,
	std::vector<CompilerError>& errors,
	std::vector<MarkovRule>& rules,
	MarkovAlphabet& alphabet)
{
	static boost::regex rx_rule("^([^\\.\\->]+)(->[\\.]*)([^\\.\\->]+)$");
	//Read rule. case #1
	boost::sregex_token_iterator iter(line.begin(), line.end(), rx_rule);
	boost::sregex_token_iterator end;
	// Read rule. case #2. 
	int index = line.find("->");
	if (iter == end && index < 0)
	{
		errors.push_back(wrongRuleDefenition(line_number, line));
	}
	else
	{
		bool is_final = false;
		std::vector<std::string> v; std::string left_part; std::string right_part;
		std::string mid;

		// cases to parse rules
		// case 1:  rules delimited by spaces.  End results is a vector of size 3
		//		    with either '->' or '->.'
		std::regex rgx("\\s+");
		//	std::regex rgx("\\-\\>");
		std::sregex_token_iterator iter(line.begin(),
			line.end(),
			rgx,
			-1);
		std::sregex_token_iterator end;
		for (int i = 0; iter != end; ++iter, ++i){
		//	std::cout << *iter << '\n';
			if (i == 0)v.push_back(*iter);
			else if (i == 1)v.push_back(*iter);
			else if (i == 2)v.push_back(*iter);
			else v.push_back(*iter);
		}
		// case 2:  Results not acceptable when delimited by space.  End results was a vector of size greater then 3.
		//		    Try to split using '->'.   Notice '->' must be preceeded and followed by white spaces.
		if (v.size() > 3)
		{
			v.erase(v.begin(), v.end());
			std::regex rgx("\\s+\\-\\>\\s+");
			std::sregex_token_iterator iter(line.begin(),
				line.end(),
				rgx,
				-1);
			std::sregex_token_iterator end;
			for (int i = 0; iter != end; ++iter, ++i){
			//	std::cout << *iter << '\n';
				if (i == 0)v.push_back(*iter);
				else if (i == 1) { 
					v.push_back("->"); 
					v.push_back(*iter);
				}
				else if (i == 2)v.push_back(*iter);
				else v.push_back(*iter);
			}

		}
		// case 3:  Results not acceptable when delimited by '->'.  End results was a vector of size 1.
		//		    Try to split using '->.'. Notice '->.' must be preceeded and followed by white spaces.
		if (v.size() == 1)
		{

			v.erase(v.begin(), v.end());
			std::regex rgx("\\s+\\-\\>\\.\\s+");
			std::sregex_token_iterator iter(line.begin(),
				line.end(),
				rgx,
				-1);
			std::sregex_token_iterator end;
			for (int i = 0; iter != end; ++iter, ++i){
			//	std::cout << *iter << '\n';
				if (i == 0)v.push_back(*iter);
				else if (i == 1) {
					v.push_back("->.");
					v.push_back(*iter);
				}
				else v.push_back(*iter);
			}
		}

			left_part = v[0];
			mid = v[1];
			right_part = v[2];
			if (mid == "->.") is_final = true;




		if (isCharsInAlphabet(line_number, left_part, errors, alphabet)
			&& isCharsInAlphabet(line_number, right_part, errors, alphabet))
		{

			MarkovRule rule(left_part, right_part, is_final, line_number);
			rules.push_back(rule);

			if(OUTPUT) std::cout << "Rule: " << left_part << is_final << right_part << std::endl;

		}

	}
}

bool parseAlphabet(int line_number,
	std::string line,
	std::vector<CompilerError>& errors,
	MarkovAlphabet& alphab,
	std::string alphabet_mark)
{
	boost::regex rx_alphabet("^" + alphabet_mark + "[\\s]*=[\\s]*\\{([^\\{\\}]*)\\}$");
	boost::sregex_token_iterator it(line.begin(), line.end(), rx_alphabet);
	boost::sregex_token_iterator end;

	bool res = false;
	//Read alphabet
	if (it == end)
	{
		res = false;

	}
	else
	{

		std::vector<std::string>  vletters(it, end);
		std::string letters_str = vletters[0];

		if(OUTPUT) std::cout << "Letters: " << letters_str << std::endl;

		std::set<char> alphabet_q;
		if (letters_str.size() > 0)
		{
			std::vector<std::string> letters;
			boost::split(letters, letters_str, boost::is_any_of(","), boost::token_compress_on);
			for (unsigned int j = 0; j< letters.size(); ++j)
			{
				std::string letter = letters[j];
				boost::trim(letter);

				if (letter.size() != 1)
				{
					errors.push_back(wrongAlphabetChar(line_number, letter));
				}
				else if (letter == "$")
				{
					errors.push_back(emptySymbolInAlphabet(line_number));
				}
				else if (forbidden_symbols.find(letter) >= 0)
				{
					errors.push_back(forbiddenInAlphabet(line_number, letter));
				}
				else
				{
					char ch = letter[0];
					if (alphabet_q.find(ch) != alphabet_q.end())
					{
						errors.push_back(charAlreadyInAlphabet(line_number, letter));
					}
					else
					{
						alphabet_q.insert(ch);
					}
				}
			}
		}

		alphab = MarkovAlphabet(alphabet_q);
		alphab.setSource(letters_str);
		res = true;

	}
	return res;
}

bool MarkovParser::parseSourceCode(std::string source_code,
	MarkovAlgorithm& algorithm,
	std::vector<CompilerError>& verrors)
{
	bool first_rule_is_readed = false;
	bool T_alphabet = false;
	bool I_alphabet = false;
	std::vector<std::string> lines;
	boost::split(lines, source_code, boost::is_any_of("\r\n"));
	verrors.clear();

	if (OUTPUT) std::cout << "Engine Parsed Rules from file" << std::endl << std::endl;

	MarkovAlphabet alphabet(true);
	MarkovAlphabet input_alphabet(true);
	std::vector<MarkovRule> rules;

	for (unsigned int i = 0; i<lines.size(); ++i)
	{
		int line_number = i + 1;
		std::string line = removeComments(lines[i]);
		boost::trim(line);

		if (line.size() > 0)
		{
			bool readed = false;
			if (!first_rule_is_readed)
			{
				if (!T_alphabet)
				{
					T_alphabet = parseAlphabet(line_number, line, verrors, alphabet, "T");
					readed = T_alphabet;
				}
				else if (!I_alphabet)
				{
					I_alphabet = parseAlphabet(line_number, line, verrors, input_alphabet, "I");

					for (char ch : input_alphabet.getAlphabet())
					{
						if (!alphabet.isInAlphabet(ch))
						{
							verrors.push_back(notInAlphabet(line_number, std::to_string(ch), alphabet));
							break;
						}
					}

					readed = I_alphabet;
				}
			}

			if (!readed)
			{
				parseRule(line_number, line, verrors, rules, alphabet);
				first_rule_is_readed = (rules.size() > 0);
			}

		}
	}

	algorithm = MarkovAlgorithm(alphabet, rules, input_alphabet);

	return verrors.size() == 0;
}
