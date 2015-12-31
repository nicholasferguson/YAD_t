#include "CompilerError.h"

CompilerError::CompilerError(const std::string &title,
                             const std::string &description,
                             int error_number,
                             int line_numer):
    _title(title),
    _description(description),
    _error_number(error_number),
    _line_numer(line_numer)
{
}
int CompilerError::getErrorNumber()
{
    return _error_number;
}

int CompilerError::getLineNumber()
{
    return _line_numer;
}

const std::string& CompilerError::getErrorTitle()
{
    return _title;
}

const std::string& CompilerError::getErrorDescription()
{
    return _description;
}

const std::string CompilerError::getFullErrorInfo()
{
    return _title + ": " + _description;
}

void CompilerError::setErrorNumber(int number)
{
    _error_number = number;
}

void CompilerError::setLineNumber(int line)
{
    _line_numer = line;
}

void CompilerError::setErrorTitle(const std::string& title)
{
    _title = title;
}

void CompilerError::setErrorDescription(const std::string& description)
{
    _description = description;
}
