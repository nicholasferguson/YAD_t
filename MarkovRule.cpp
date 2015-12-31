#include "MarkovRule.h"

MarkovRule::MarkovRule(const std::string& left_patr,
                       const std::string& right_part,
                       bool is_final,
                       int line_number):
    _pattern(left_patr),
    _substitution(right_part),
    _is_final_rule(is_final),
    _line_number(line_number)
{
}
bool MarkovRule::isFinalRule() const
{
    return _is_final_rule;
}

const std::string& MarkovRule::getLeftPart() const
{
    return _pattern;
}

const std::string& MarkovRule::getRightPart() const
{
    return _substitution;
}

int MarkovRule::getLineNumber() const
{
    return _line_number;
}
const std::string MarkovRule::getFullRule() const
{
    return _pattern + "->" + _substitution;
}
void MarkovRule::setFinalRule(bool is_final)
{
    _is_final_rule = is_final;
}

void MarkovRule::setLeftPart( std::string& str)
{
    _pattern = str;
}

void MarkovRule::setRightPart(std::string& str)
{
    _substitution = str;
}

void MarkovRule::setLineNumber(int line_number)
{
    _line_number = line_number;
}
