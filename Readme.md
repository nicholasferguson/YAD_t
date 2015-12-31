=====================================================================
Into.  Markov Algorithm.  Ported from QT/YAD Studio into a std/boost console app.
       Refactored.  Will run all 5 rule sets from Rosettacode.org and 2 rule sets from wiki page on Markov Algorithm. And 2 rule sets from YAD studio.

=====================================================================
This was used a preliminary vehicle to study implementations of Markov Algorithms

I extracted Markov Algorithm related files from Yad.Studio, https://github.com/Yad-Studio/YAD-Studio/	
and ported these files from QT over to std / boost, as a Visual Studio 2013 console application

You can run YAD Studio as a checker.  This console app will run
* 2 test files, used by YAD Studio as their examples:  multiply.yad and mirrow.yad
* 2 test examples from a wiki page.
	https://en.wikipedia.org/wiki/Markov_algorithm
* 5 test examples from Rosettacode.org page, copied into files. ( see below for more details)
	http://rosettacode.org/wiki/Execute_a_Markov_algorithm

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
Done ====
=====================================================================
* Extracted files from YAD Studio and QT to work Markov Algorithm files from YAD Studio.
* Converted these files from QT over to std and boost
* This is a Visual Studio 2013 console application.
* Also converted one function from QT, wc2rx.  See wc2rx.cpp
  Made wc2rx friendly to five rule sets from Rosettacode.org
  
=====================================================================
Todo =====
=====================================================================
Todo #1 When this app loads up rules from a file...
$ -> S*   "works"
$->S*     does not work.  Parse of '->' and '->.' requres spaces.

Todo #2: Clean up wc2rx.cpp
	     It is a bit hacked to run these nine examples.

Todo #3: Process a YAD File with real regex...processed as regex symbols.
	     This will need wc2rx.cpp to be refactored.

Todo #4: Refactor Preprocessor OUTPUT=true to control std:cout's

Todo #5: Reading in file, line starting as //TASK becomes ASK.
         Correction requires a refactor of std::string rstrip(const std::string& str) in YadFile.cpp

Todo #6: Refactor returns from test functions in YAD_t.cpp to work with
		 See: std::string CompareTestResults(std::string filename, std::string input)
		 
=====================================================================
Included Tests =(9)==== see YAD_t.cpp
===================================================================== 
wiki page:  		https://en.wikipedia.org/wiki/Markov_algorithm
Rosettacode.org page: 	http://rosettacode.org/wiki/Execute_a_Markov_algorithm
YAD Studio page: 	https://github.com/Yad-Studio/YAD-Studio

===================================================================== 
Test# Details 
1) From wiki page.   ( Hard coded test. )
   Input:   I bought a B of As from T S.
   Output:  I bought a bag of apples from my brother.
2) From wiki page.   ( Hard coded test. )
   Input: 101
   Output: |||||  ( binary 101 into base 10 using sticks....5 sticks)
3) From YAD Studio. I renamed their file renamed as YAD.Studo.mirrow.yad
   Input: cabbbbaaaabbbbaabbcccccc
   Output:
4) From YAD Studio. I renamed their file renamed as YAD.Studo.multiply.yad
   Input: |||#||   i.e. 3*2
   Output ||||||   i.e. 6
5) From Rosettacode.org  Rosetta.ruleset1.yad (This rules file is extracted from Wikipedia)
   Input:  I bought a B of As from T S
   Output: I bought a bag of apples from my brother
6) From Rosettacode.org  Rosetta.ruleset2.yad (Slightly modified from the rules on Wikipedia)
   Input:  I bought a B of As from T S
   Output: I bought a bag of apples from T shop
7) From Rosettacode.org  Rosetta.ruleset3.yad (BNF Syntax testing rules)
   Input:  I bought a B of As W my Bgage from T S
   Output: I bought a bag of apples with my money from T shop
8) From Rosettacode.org  Rosetta.ruleset4.yad (Unary Multiplication Engine)
   Input:  _1111*11111_
   Output: 11111111111111111111
9) From Rosettacode.org  Rosetta.ruleset5.yad (Turing machine: three-state busy beaver)
   Input:  000000A000000
   Output: 00011H1111000
   
=====================================================================
Sample console app output running Rosetta.ruleset3.yad
=====================================================================
Details from test file: Rosetta.ruleset3.yad
Source: NF Syntax testing rules
A -> apple
WWWW -> with
Bgage -> ->.*
B -> bag
->.* -> money
W -> WW
S -> shop.
T -> the
the shop -> my brother
a never used ->. terminating rule




History:
// I bought a B of As W my Bgage from T S.

Engine Parsed Rules from file

Rule: A0apple
Rule: WWWW0with
Rule: Bgage0->.*
Rule: B0bag
Rule: ->.*0money
Rule: W0WW
Rule: S0shop.
Rule: T0the
Rule: the shop0my brother
Rule: a never used1terminating rule

Input_string before it is transformed: I bought a B of As W my Bgage from T S

Output from running algorithm:
Step # 1
Rule: A -> apple
Before: I bought a B of As W my Bgage from T S
After: I bought a B of apples W my Bgage from T S

Step # 2
Rule: Bgage -> ->.*
Before: I bought a B of apples W my Bgage from T S
After: I bought a B of apples W my ->.* from T S

Step # 3
Rule: B -> bag
Before: I bought a B of apples W my ->.* from T S
After: I bought a bag of apples W my ->.* from T S

Step # 4
Rule: ->.* -> money
Before: I bought a bag of apples W my ->.* from T S
After: I bought a bag of apples W my money from T S

Step # 5
Rule: W -> WW
Before: I bought a bag of apples W my money from T S
After: I bought a bag of apples WW my money from T S

Step # 6
Rule: W -> WW
Before: I bought a bag of apples WW my money from T S
After: I bought a bag of apples WWW my money from T S

Step # 7
Rule: W -> WW
Before: I bought a bag of apples WWW my money from T S
After: I bought a bag of apples WWWW my money from T S

Step # 8
Rule: WWWW -> with
Before: I bought a bag of apples WWWW my money from T S
After: I bought a bag of apples with my money from T S

Step # 9
Rule: S -> shop.
Before: I bought a bag of apples with my money from T S
After: I bought a bag of apples with my money from T shop.

Step # 10
Rule: T -> the
Before: I bought a bag of apples with my money from T shop.
After: I bought a bag of apples with my money from the shop.

Final string output from running algorithm: I bought a bag of apples with my money from the shop.
