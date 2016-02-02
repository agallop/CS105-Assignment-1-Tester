# CS105-Assignment-1-Tester

WARNING   WARNNGg   WARNING   WARNING

 Running,                                     
	 make clean                                 
 will delete                              
	 assignment1.cpp                            
	 assignment1                     
	 Outputs/ directory contents                
 I don't see why one would decide to run this,
 but better safe than sorry                   

WARNING   WARNING   WARNING   WARNING

BACKGROUND:
	This is a tester I created for an assignemnt on CS105 - c++ programming where
	the goal was to create a program that took text with an message encoded
	in an uncommonly used (said to probably only be used by it's creator) cypher
	
	In each line, the most frequently occuring word was the next work in the message
	Lines with no words are ignored
	When there is a tie for the most frequent word, USe the word that occurs first
	To simlplify, words are seperated by any non-alphabetic character
		Example: "don't" is counted as two words, "don" and "t"
	In the output, print a space after each word. The tester ignores whitespace at the end of the output.


HOW TO:
To run the tester, place assignment1.cpp into the directory and run
	make;
	./driver

The tester will run your instances of your solution with the input files
in the Inputs/ directory and output from your program will be stored in the OutPuts/ directory

The files used to determine if your outputs 
 are correct  are in the ExpectedOutputs/ directory
 and editing these files might make the tester 
 evaluate incorrectly

How expected output files are stuctured:
[Number of expected characters*]
[Expected Output]
[EOF]

*not including trailing whitespace
