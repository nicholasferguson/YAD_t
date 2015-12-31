#ifndef MARKOVALPHABET_H
#define MARKOVALPHABET_H

#include <set>
#include <stdlib.h>
#include <string>

class MarkovAlphabet
{
public:
    MarkovAlphabet(const std::set<char>& alphabeth=std::set<char>());
    MarkovAlphabet(const bool is_auto);

    bool isInAlphabet(char c) const;
    std::set<char> getAlphabet() const;

    std::string getAllChars() const;
    std::string getSource() const;
    void setSource(std::string source);

    bool isAuto() const;
private:
    std::set<char> _chars;
    std::string _all_chars;
    std::string _source;
    bool _is_auto;
};

#endif // MARKOVALPHABET_H
