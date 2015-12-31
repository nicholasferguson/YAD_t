#ifndef RUNERROR_H
#define RUNERROR_H
#include <string>

class RunError
{
public:
    RunError(const std::string& title, const std::string& description,
             int error_numer);

    int getErrorNumber();
    const std::string& getErrorTitle();
    const std::string& getErrorDescription();
    /**
     * @brief getFullErrorInfo
     * @return ErrorTitle + ErrorDescription
     */
    const std::string getFullErrorInfo();

    void setErrorNumber(int number);
    void setErrorTitle(const std::string& title);
    void setErrorDescription(const std::string& description);
private:
    // each error type has own number
    int _error_number;

    std::string _title;
    std::string _description;
};

#endif // RUNERROR_H
