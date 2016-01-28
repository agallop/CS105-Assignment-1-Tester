#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#define TESTCOUNT 4 //to change when adding tests

//Function prototypes
pid_t Fork();
int compare(std::string expected, std::string output);

main(int argc, char* argv[]){
	std::string assignment = "./assignment1"; 
	for(int i = 0; i < TESTCOUNT; i++){
		//building filepath for output
		std::ostringstream out;
		out << "Outputs/" << i << ".out";

		//Forking and getting pid
		pid_t pid = Fork();

		//Child process
		if(pid == 0){
			//building filepath for input
			std::ostringstream in;
			in << "Inputs/"<< i << ".in" ;

			//Redirecting input to cin 
			int inf = open(in.str().data(), S_IRUSR);
			dup2(inf, 0);
			close(inf);

			//Redirecting output to cout
			int outf = open(out.str().data(),
				O_WRONLY | O_TRUNC | O_CREAT, 
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			dup2(outf, 1);
			close(outf);

			//executing assignment1
			execl(assignment.data(), assignment.data(), (char*) 0);
		}
		//Parent Process
		//waits for child process to finish
		int* status;
		waitpid(pid, status, 0);

		//build file path for expected output file
		std::ostringstream e;
		e << "ExpectedOutputs/" << i << ".e";

		//Checks if test passed or failed
		if(compare(e.str(),out.str())){
			std::cout << "Test " << i << " Passed\n";
		} else
			std::cout << "Test " << i << " Failed\n";
	}
}


//fork() wrapper function
//returns pid returned by fork()
pid_t Fork(){
	pid_t pid = fork();

	//error checking
	if(pid == -1){
		std::cerr << "Fork failed!\n";
		std::exit(-1);
	}

	return pid;
}

//Compares the expected output to the actual eoutput
//Ignores whitespace at end of output
//Expected output files should be structured
/**************************************
 * [Positive Integer]                 *
 * [Expected Output]                  *
 **************************************/
//Where the integer is how many chars
//to read from expexted output till the last
//alpha char is reached
int compare(std::string expected, std::string output){

	//opens streams
	std::ifstream exp (expected.data());
	std::ifstream out (output.data());
	std::string expLine;
	std::string outLine;

	//Finds the number of chars to read
	std::getline(exp, expLine);
	int charCount = atoi(expLine.data());

	//Gets lines to compare
	std::getline(exp, expLine);
	std::getline(out, outLine);

	//returns false if output is too short
	if(charCount > outLine.size()){
		return 0;
	}

	int i;
	//itterates through both streams to see if each
	//character is the same (case-sensitive)
	for(i = 0; i < charCount; i++){
		if(expLine[i] != outLine[i])
			return 0;
	}

	//check to make sure there isn't anything after last expected word
	for(i; i < outLine.size(); i++){
		if(!isspace(outLine[i]))
			return 0;
	}

	//One last check to be sure EOF was reached and closes streams
	int ret = !(std::getline(exp, expLine));
	exp.close();
	out.close();
	return ret;
}
