#ifndef MARKOVRUNMANAGER_H
#define MARKOVRUNMANAGER_H

#include "MarkovAlgorithm.h"
#include "RunError.h"
#include <set>
#include <functional>
#include <string>


class StepResult
{
public:
    StepResult(std::string output,
               int step_id):
        _output(output),
        _step_id(step_id)
    {
    }

    std::string _output; //The word after rule on this step was applied
    int _step_id; //The id of step
};
bool operator <(const StepResult& a, const StepResult& b);
bool operator==(const StepResult& a, const StepResult& b);

inline unsigned int qHash(const StepResult& a)
{
	std::hash<std::string>fn;
	return  fn( a._output );

}

class MarkovRunManager
{
  //  Q_OBJECT
public:
    static MarkovRunManager* getInstance();

private:
    MarkovRunManager();
    MarkovRunManager(MarkovRunManager const&);
    void operator=(MarkovRunManager const&);
    static MarkovRunManager* _instance;
public:
    //the alphabet and rules list.
    //It can be changed while algorithm is running.
    MarkovAlgorithm _algorithm;

    //the input word of last run.
    std::string _input_word;

    //the number of steps made.
    int _steps_made;

    //the word after last rule was applied
    std::string _word_after_last_step;

    //break points.
    std::set<int> _break_points;

    //stores each step result to prevent program from cycle.
    std::set<StepResult> _steps_history;

    //whether the program now in debug mode.
    bool _is_debug_mode;

    //This function return true if the next should be made and false otherwise.
    bool findAndApplyNextRule(bool isEscaping);

    bool _stop_on_next_step;

    int getStepNumberOfValue(std::string word);
    bool choseAndUseRule(std::string &word, MarkovRule &rule, bool isEscaping);
    bool _terminate_on_next_step;

    void doStartDebug(std::string word, bool stop_at_first_step, bool isEscaping);

    bool isInputValid(std::string input_word);
// slots:
    //called when new compiled algorithm is available.
    void setAlgorithm(MarkovAlgorithm algorithm);

    //true if the last version of source code is ready for running.
    //When changed the canRunSourceCode should be emited.
    void setCanRunSourceCode(bool can);

    //starts running process.
	void runWithoutDebug(std::string input_word, bool isEscaping);

    //starts running with debug.
	void runWithDebug(std::string input_word, bool isEscaping);

	void runWithDebugStepByStep(std::string input_word, bool isEscaping);

    // add break point to set
    void addBreakPoint(int line_number);

    //removes break point from set
    void removeBreakPoint(int line_number);

    //called when user clicks Next Step in debug window.
	void debugNextStep(bool isEscaping);

    //called when user clicks Continue in debug window
	void debugContinue(bool isEscaping);

    //called when user clicks Stop in debug window
    void debugStop();


    void terminateRun();
//signals
    //emited when setCanRunSourceCode is called
    void canRunSourceCode(bool);

    void runWithoutDebugStarted(std::string input_word);

    void runWithoutDebugFinishSuccess(std::string input_word,
                                      std::string output_word,
                                      int steps_made);

    void runWithoutDebugFinishFail(std::string input_word,
                                   RunError error,
                                   int steps_made);

    void runStepsMade(int steps_made);

    void debugStarted(std::string input_word);

    void debugFinishSuccess(std::string input_word,
                            std::string output_word,
                            int steps_made);

    void debugFinishFail(std::string input_word,
                         RunError error,
                         int steps_made);

    void debugStepFinished(int step_number,
                           std::string before_step,
                           std::string after_step,
                           MarkovRule rule);

    void debugBreakPointReached(int line_number);
};




#endif // MARKOVRUNMANAGER_H
