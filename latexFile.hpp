#ifndef DEF_LATEXFILE
#define DEF_LATEXFILE

/*! 
LatexFile class
imports a LaTeX main file and flattens it. 
*/

#include<iostream> 
// #include <sys/stat.h>
#include <filesystem>

class LatexFile 
{
public:
    LatexFile(std::string filename, bool verbose);
    bool flatMeMaRace();
    bool flatMeOnce(bool firstTime);
    bool checkFlat(bool firstTime);
    bool copyRepo();
    bool backToTheRoots();
protected: 
    std::string m_filename;
    // std::string m_filenameFlat;
    std::string m_path;
    std::string m_pathFlat;
    bool m_imFlat;
    bool m_verbose;
};



#endif