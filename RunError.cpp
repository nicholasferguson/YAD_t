#include "RunError.h"

RunError::RunError(const std::string& title,
                   const std::string& description,
                   int error_numer):
    _title(title),
    _description(description),
    _error_number(error_numer)
{
}
int RunError::getErrorNumber()
{
    return _error_number;
}

const std::string& RunError::getErrorTitle()
{
    return _title;
}

const std::string& RunError::getErrorDescription()
{
    return _description;
}

const std::string RunError::getFullErrorInfo()
{
    return std::to_string(_error_number) + ": " + _description;
}

void RunError::setErrorNumber(int number)
{
    _error_number = number;
}
void RunError::setErrorTitle(const std::string& title)
{
    _title = title;
}

void RunError::setErrorDescription(const std::string& description)
{
    _description = description;
}
