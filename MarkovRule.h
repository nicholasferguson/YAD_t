#ifndef MARKOVRULE_H
#define MARKOVRULE_H
#include <string>

class MarkovRule
{
public:
    MarkovRule(const std::string& left_patr="", const std::string& right_part="",
               bool is_final = false, int line_number=-1);

    bool isFinalRule() const;
    const std::string& getLeftPart() const;
    const std::string& getRightPart() const;
    int getLineNumber() const;
    const std::string getFullRule() const;

    void setFinalRule(bool is_final);
    void setLeftPart(std::string& str);
    void setRightPart(std::string& str);
    void setLineNumber(int line_number);

private:
    //left part of the rule
    std::string _pattern;
    //right part of the rule
    std::string _substitution;

    //if rule is final then algorithm will stop after this rule execution
    bool _is_final_rule;

    //number of line where the rule was found
    int _line_number;
};

#endif // MARKOVRULE_H
