
=====================================================================
Introduction ====
* Markov Algorithm.  
* This was used as a preliminary vehicle to study implementations of Markov Algorithms
* Ported from QT/YAD Studio into a std/boost console app, built with Visual Studio 2013.
* Refactored so it will run all 
* 5 rule sets from Rosettacode.org (http://rosettacode.org/wiki/Execute_a_Markov_algorithm) and 
* 2 rule sets from s wiki page on Markov Algorithm. (https://en.wikipedia.org/wiki/Markov_algorithm) and 
* 2 rule sets from YAD studio.
* Console app outputs to console each step of a rule transitioning input into final output.

* What this study shows... is how to devise a dictionary of rules and a rule engine.  
* It is Markov: 
* Because it is applied over a sequence requiring that an initial rule be applied. 
* And subsequent rules are applied conditional on a previous unique rule having been applied.
* And there is a rule that when applied will stop this process.   
* Or applicable rules have been exhausted, and this process will thus stop.

* Needed research:  How to compute probable min/max steps to completion, giving an alphabet, rule set and input string.

=====================================================================
To Build ====
=====================================================================
* Visual Studio 2012 Express
* From Express open YAD_t.sln
* In Solution 'property page' provide your path to your Boost.org includes and libraries.
* Build
* Run.
Main file: YAD_t.cpp  
You can comment out various test functions in its main().

=====================================================================
Caveats for rules in files ====
=====================================================================
* U -> S* is acceptable.  Notice spaces.
* U->S* is not acceptable.  Notice lack of spaces.
* U->.S  is not acceptable  Notice lack of spaces.
* U ->. S* is acceptable.  Notice spaces.
* whattheheck ->     is not acceptable. Notice right hand side of '->' is blank.
* whattheheck -> ''  is acceptable.  Notice right hand side has '' to indicate blank.

=====================================================================
Done ====
=====================================================================
* Converted one function from QT, wc2rx.  See wc2rx.cpp
* Made wc2rx friendly to five rule sets from Rosettacode.org
  
=====================================================================
Todo ====
=====================================================================
* Todo #1 When this app loads up rules from a file.
		- $ -> S*   "works"
		- $->S*     does not work.  
		- Parse of '->' and '->.' currently requires spaces before and after.

* Todo #2: Clean up wc2rx.cpp and MarkovParser.cpp
		- They are a bit hacked to run these nine examples.
		- It lacks a C++ type explicit pattern/algorithm.

* Todo #3: Process a YAD File with real regex...processed as regex symbols.
		- This will need wc2rx.cpp to be refactored.

* Todo #4: Refactor Preprocessor OUTPUT=true to control std:cout's

* Todo #5: Reading in file, line starting as //TASK becomes ASK.
		- Correction requires a refactor of std::string rstrip(const std::string& str) in YadFile.cpp

* Todo #6: Refactor returns from test functions in YAD_t.cpp to work with
		- See: std::string CompareTestResults(std::string filename, std::string input)
		 
=====================================================================
Tests(9) ==== 
===================================================================== 
* see YAD_t.cpp
* Wiki page:  				https://en.wikipedia.org/wiki/Markov_algorithm
* Rosettacode.org page: 	http://rosettacode.org/wiki/Execute_a_Markov_algorithm
* YAD Studio page: 			https://github.com/Yad-Studio/YAD-Studio

===================================================================== 
Test# Details ====
===================================================================== 
* 1 From wiki page.   ( Hard coded test in YAD_t.cpp. )
   - Input:   I bought a B of As from T S.
   - Output:  I bought a bag of apples from my brother.
   - # Rules: 5
   - # Rules Alphabet:
   - # Input Alphabet: 
   - # Steps: 5
* 2 From wiki page.   ( Hard coded test in YAD_t.cpp. )
   - Input: 101
   - Output: |||||  ( binary 101 into base 10 using sticks....5 sticks)
   - # Rules: 3
   - # Rules Alphabet: 
   - # Input Alphabet: 
   - # Steps: 8
* 3 From YAD Studio file. I renamed their file as YAD.Studo.mirrow.yad
   - Input:  cabbbbaaaabbbbaabbcccccc
   - Output: ccccccbbaabbbbaaaabbbbac
   - # Rules: 21
   - # Rules Alphabet: 9
   - # Input Alphabet: 3
   - # Steps: 351
* 4 From YAD Studio file. I renamed their file as YAD.Studo.multiply.yad
   - Input: |||#||   i.e. 3*2
   - Output ||||||   i.e. 6
   - # Rules: 12
   - # Alphabet: 8
   - # Input Alphabet: 2
   - # Steps: 35
* 5 From Rosettacode.org  Rosetta.ruleset1.yad (This rules file is extracted from Wikipedia)
   - Input:  I bought a B of As from T S
   - Output: I bought a bag of apples from my brother
   - # Rules: 6
   - # Rules Alphabet: 
   - # Input Alphabet: 
   - # Steps: 4
* 6 From Rosettacode.org  Rosetta.ruleset2.yad (Slightly modified from the rules on Wikipedia)
   - Input:  I bought a B of As from T S
   - Output: I bought a bag of apples from T shop
   - # Rules: 6
   - # Rules Alphabet:
   - # Input Alphabet: 
   - # Steps: 3
* 7 From Rosettacode.org  Rosetta.ruleset3.yad (BNF Syntax testing rules)
   - Input:  I bought a B of As W my Bgage from T S
   - Output: I bought a bag of apples with my money from T shop
   - # Rules: 10
   - # Rules Alphabet: 
   - # Input Alphabet: 
   - # Steps: 10
* 8 From Rosettacode.org  Rosetta.ruleset4.yad (Unary Multiplication Engine)
   - Input:  _1111*11111_  i.e. 4*5
   - Output: 11111111111111111111  i.e. 20
   - # Rules: 20
   - # Rules Alphabet: 
   - # Input Alphabet: 
   - # Steps: 165
* 9 From Rosettacode.org  Rosetta.ruleset5.yad (Turing machine: three-state busy beaver)
   - Input:  000000A000000
   - Output: 00011H1111000
   - # Rules: 10
   - # Rules Alphabet: 
   - # Input Alphabet: 
   - # Steps: 13
   
=====================================================================
Sample console app output running a ruleset #3 from Rosettacode.org as a file named Rosetta.ruleset3.yad
=====================================================================

* Details from test file: Rosetta.ruleset3.yad
* BNF Syntax testing rules

- A -> apple
- WWWW -> with
- Bgage -> ->.*
- B -> bag
- ->.* -> money
- W -> WW
- S ->. shop
- T -> the
- the shop -> my brother
- a never used ->. terminating rule

- History:
- // I bought a B of As W my Bgage from T S.

= Engine parses these rules as:
* Note: -> is replaced by 0
* Note: ->. is replaced by 1  (this symbol a final rule that ends transition)

* Rule1: A0apple
* Rule2: WWWW0with
* Rule3: Bgage0->.*
* Rule4: B0bag
* Rule5: ->.*0money
* Rule6: W0WW
* Rule7: S1shop
* Rule8: T0the
* Rule9: the shop0my brother
* Rule:10 a never used1terminating rule

- Input_string before its transition: I bought a B of As W my Bgage from T S

= Output from running algorithm:
...
###### Step # 1
- Rule: A -> apple
- Before: I bought a B of As W my Bgage from T S
- After: I bought a B of apples W my Bgage from T S

###### Step # 2
- Rule: Bgage -> ->.*
- Before: I bought a B of apples W my Bgage from T S
- After: I bought a B of apples W my ->.* from T S

###### Step # 3
- Rule: B -> bag
- Before: I bought a B of apples W my ->.* from T S
- After: I bought a bag of apples W my ->.* from T S

###### Step # 4
- Rule: ->.* -> money
- Before: I bought a bag of apples W my ->.* from T S
- After: I bought a bag of apples W my money from T S

###### Step # 5
- Rule: W -> WW
- Before: I bought a bag of apples W my money from T S
- After: I bought a bag of apples WW my money from T S

###### Step # 6
- Rule: W -> WW
- Before: I bought a bag of apples WW my money from T S
- After: I bought a bag of apples WWW my money from T S

###### Step # 7
- Rule: W -> WW
- Before: I bought a bag of apples WWW my money from T S
- After: I bought a bag of apples WWWW my money from T S

###### Step # 8
- Rule: WWWW -> with
- Before: I bought a bag of apples WWWW my money from T S
- After: I bought a bag of apples with my money from T S

###### Step # 9
- Rule: S ->. shop
- Before: I bought a bag of apples with my money from T S
- After: I bought a bag of apples with my money from T shop.


###### Final string output from running algorithm: 
- I bought a bag of apples with my money from T shop.

Summary of why rules stopped being applied.
Step #9 applies Rule #7 of type "LHS ->. RHS" and '->.' indicates final rule to be applied.

