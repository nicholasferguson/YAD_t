#ifndef COMPILERERROR_H
#define COMPILERERROR_H
#include <string>

class CompilerError
{
public:
    CompilerError( const std::string& title="",
                   const std::string& description="",
                   int error_number=-1,
                   int line_numer=-1);

    int getErrorNumber();
    int getLineNumber();
    const std::string& getErrorTitle();
    const std::string& getErrorDescription();
    /**
     * @brief getFullErrorInfo
     * @return ErrorTitle + ErrorDescription
     */
    const std::string getFullErrorInfo();

    void setErrorNumber(int number);
    void setLineNumber(int line);
    void setErrorTitle(const std::string& title);
    void setErrorDescription(const std::string& description);

private:
    // each error type has own number
    int _error_number;

    //number of line, where the error was occurred
    int _line_numer;

    std::string _title;
    std::string _description;
};

#endif // COMPILERERROR_H
