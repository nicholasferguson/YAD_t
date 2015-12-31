#ifndef MARKOVPARSER_H
#define MARKOVPARSER_H
#include "MarkovAlgorithm.h"
#include "CompilerError.h"
#include <vector>

class MarkovParser
{
public:
    /**
     * @brief parses the source code
     * @param source_code code to parse
     * @param algorithm output algorithm
     * @param errors output errors
     * @return returns true if there are no errors and false otherwise.
     */
    static bool parseSourceCode(std::string source_code,
                                MarkovAlgorithm& algorithm,
                                std::vector<CompilerError>& verrors);
private:
    MarkovParser();

};

#endif // MARKOVPARSER_H
