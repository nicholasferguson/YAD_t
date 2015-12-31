#include "MarkovAlphabet.h"

MarkovAlphabet::MarkovAlphabet(const std::set<char> &alphabeth):
    _chars(alphabeth), _all_chars("$"), _is_auto(false)
{
    for (char ch :  _chars)
    {
        _all_chars += ch;
    }
}
MarkovAlphabet::MarkovAlphabet(const bool is_auto)
    : _is_auto(is_auto)
{

}

std::set<char> MarkovAlphabet::getAlphabet() const
{
    return _chars;
}

std::string MarkovAlphabet::getAllChars() const
{
    return _all_chars;
}
bool MarkovAlphabet::isAuto() const
{
    return _is_auto;
}
std::string MarkovAlphabet::getSource() const
{
    return _source;
}
void MarkovAlphabet::setSource(std::string source)
{
    _source = source;
}

bool MarkovAlphabet::isInAlphabet(char c) const
{
    //empty symbol
    if(c=='$' || _is_auto)
        return true;

	if (_chars.find(c) != _chars.end())
		return false;
	return true;
}
