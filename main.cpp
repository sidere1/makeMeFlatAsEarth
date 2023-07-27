/*! 
Main file
creates a LatexFile class. 
*/

#define WHEREAMI cout << endl << "no crash until line " << __LINE__ << " in the file " __FILE__ << endl << endl;

#include <iostream>
#include <string>
#include <cassert>
#include "latexFile.hpp"

#include <algorithm>

using namespace std;


// dixit stackoverflow
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
        return *itr;
    return 0;
}
// idem 
bool cmdOptionExists(char** begin, char** end, const std::string& option){return std::find(begin, end, option) != end;}



int main(int argc, char** argv)
{
    bool verbose(false);
    int minParams(2);
	assert(argc >= minParams && "Please provide the LaTeX main file as last parameter. Or use -h to display help.");

    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        cout << "Usage : " << endl; 
        cout << "makeMeFlatAsEarth [-hv] path/to/main.tex" << endl << endl; 
        cout << "options : " << endl; 
        cout << "   -h : display help" << endl; 
        cout << "   -v : verbose mode" << endl; 
        minParams++;
        return 0;
    }
    if(cmdOptionExists(argv, argv+argc, "-v"))
    {
        verbose = true;
        minParams++;
        assert(argc >= minParams && "-v please provide the LaTeX main file as parameter in the command line");
    }
    string filename (argv[argc-1]);
	
    LatexFile l(filename, verbose);
    l.flatMeMaRace();
    
    return 0;
}
