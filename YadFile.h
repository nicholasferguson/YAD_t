#ifndef YADFILE_H
#define YADFILE_H
#include <vector>
#include <string>

/**
 * @brief Saves and loads data from file
 */
class YadFile
{
public:
    /**
     * @brief YadFile
     * @param source_code complete source code (with comments)
     * @param history history of launches
     */
    YadFile(std::string source_code,
            std::vector<std::string> history);

    /**
     * @brief Returns source code
     * @return
     */
    std::string getSourceCode() const;

    /**
     * @brief Returns history of launches
     * @return
     */
    std::vector<std::string> getHistory() const;

    /**
     * @brief  method saves to file source code and history to a given file.
     * When any error occurs then
     * the method should throw QException with error description
     * @param file_name
     */
    void saveToFile(std::string file_name) const;

    /**
     * @brief  method reads source code and history from file.
     * When any error occurs then the method should throw
     * QException with error description
     * @param file_name
     * @return
     */
    static YadFile readFromFile(std::string file_name);
private:


    /**
     * @brief complete source code (with comments)
     */
    std::string _source_code;
    /**
     * @brief history of launches
     */
    std::vector<std::string> _history;

};

#endif // YADFILE_H
