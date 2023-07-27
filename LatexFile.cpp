#include "latexFile.hpp"
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;

#define WHEREAMI cout << endl << "no crash until line " << __LINE__ << " in the file " __FILE__ << endl << endl;


LatexFile::LatexFile(std::string filename, bool verbose):m_filename(filename), m_imFlat(false), m_verbose(verbose)
{
    size_t pos1 = m_filename.find_last_of('/');
    char myChar = m_filename[pos1];
    assert(myChar == '/' && "expected a full path to the main setup file ");
    m_path = m_filename.substr(0,pos1);
    m_pathFlat = m_path + "_flat";
    m_filename = m_filename.substr(pos1+1, m_filename.size());
    if(m_verbose)
    {
        cout << "filename : " << m_filename << endl; 
    }
    if(m_verbose)
    {
        cout << "path : " << m_path << "; new path : " << m_pathFlat << endl; 
    }
}


bool LatexFile::flatMeMaRace()
{
    if (!copyRepo())
    {
        if (m_verbose)
            cout << "could not create the directory " << m_pathFlat << endl;
        return false; 
    }
    if (m_verbose)
        cout << "Directory " << m_pathFlat << " successfully created."<< endl;

    bool firstTime(true);
    while(!checkFlat(firstTime))
    {
        if (!flatMeOnce(firstTime))
        {
            if (m_verbose)
            {
                cout << "flatMeOnce failed successfully :( " << endl;
            }   
            return false; 
        }
        if (m_verbose)
            cout << "flatMeOnce finished successfully :) " << endl; 
        firstTime = false; 
    };
    if (!backToTheRoots())
    {
        if (m_verbose)
            cout << "could not bring all figures to the root" << m_pathFlat << endl;
        return false; 
    }

    return true; 
}

bool LatexFile::flatMeOnce(bool firstTime)
{
    namespace fs = boost::filesystem;
    string line("");
    string filename("");
    string inputFilename("");
    const string key1("\\include{");
    const string key2("\\input{");
    const string key3("%");
    bool insert(false);
    size_t found1;
    size_t found2;

    if (firstTime)
    {
        filename = m_path+'/'+m_filename;
    }
    else
    {
        fs::remove(m_pathFlat+'/'+m_filename+"_temp");
        fs::copy_file(m_pathFlat+'/'+m_filename, m_pathFlat+'/'+m_filename+"_temp");
        fs::remove(m_pathFlat+'/'+m_filename);
        filename = m_pathFlat+'/'+m_filename+"_temp";
    }
    ifstream in(filename);
    if (!in)
    {
        cout << "could not open " << filename << " to check perform flatMeOnce" <<endl;
        return false; 
    }
    ofstream out(m_pathFlat+'/'+m_filename); 
    if (!out)
    {
        cout << "could not open " << m_pathFlat+'/'+m_filename << " to write a flatter version of " << filename <<endl;
        return false; 
    }
    while(getline(in,line))
    {
        insert = false; 
        found1 = line.find(key1, 0);
        found2 = line.find(key2, 0);
        if ((found1 != string::npos) || (found2 != string::npos))
        {
            found1 = line.substr(0, min(found1, found2)).find(key3, 0);
            if (found1 == string::npos)
            {
                size_t pos1 = line.find_first_of('{');
                size_t pos2 = line.find_first_of('}');
                inputFilename = line.substr(pos1+1, (pos2-pos1-1));
                cout << "I found " << line << " so I'm going to insert " << inputFilename << endl;
                char myChar = line[pos1];
                assert(myChar == '{' );
                myChar = line[pos2];
                assert(myChar == '}' );
                insert = true; 
            }
        }
        if (insert)
        {
            if(!fs::exists(m_path+'/'+inputFilename))
            {
                cout << "could not open " << m_path + '/' + inputFilename << " to insert its content " <<endl;
                inputFilename+=".tex";
            }
            if(!fs::exists(m_path+'/'+inputFilename))
            {
                cout << "could not open " << m_path + '/' + inputFilename <<" either " <<endl;
                return false; 
            }
            ifstream inInsert(m_path + '/' + inputFilename);
            if (!inInsert)
            {
                inputFilename+=".tex";
                ifstream inInsert(m_path + '/' + inputFilename);
                if (!inInsert)
                {
                    
                    cout << "could not open " << m_path + '/' + inputFilename << " to insert its content " <<endl;
                    return false; 
                }
            }
            if(m_verbose)
            {
                cout << "Successfully opened " << m_path + '/' + inputFilename << endl;
            }
            // getline(inInsert,line);
            // cout << line << endl;
            while (getline(inInsert,line))
            {
                out << line << endl;
            }
        }
        else 
        {
            out << line << endl;
        }
        
    }
    return true;
}

bool LatexFile::checkFlat(bool firstTime)
{
    string line("");
    string filename("");
    bool isFlat(true);
    const string key1("\\include{");
    const string key2("\\input{");
    const string key3("%");
    size_t found1;
    size_t found2;

    if (firstTime)
        filename = m_path+'/'+m_filename;
    else 
        filename = m_pathFlat+'/'+m_filename;
    ifstream in(filename);
    if (!in)
    {
        cout << "could not open " << filename << " to check flatness" <<endl;
        return false; 
    }

    // if (m_verbose) 
    //     cout << "checking if " << filename << " is flat " << endl;

    while (getline(in,line))
    {
        found1 = line.find(key1, 0);
        found2 = line.find(key2, 0);
        if ((found1 != string::npos) || (found2 != string::npos))
        {
            found1 = line.substr(0, min(found1, found2)).find(key3, 0);
            if (found1 == string::npos)
            {
                isFlat = false; 
                if (m_verbose) 
                    cout << "Not flat : I found " << line << endl;
            }
        }
    }
    if (m_verbose)
    {
        if (isFlat)
            cout << filename << " is flat" << endl;
        else 
            cout << filename << " is not flat yet" << endl;
    }
    return isFlat; 
}

bool LatexFile::copyRepo()
{
    namespace fs = boost::filesystem;
    try {
        // fs::copy_file(m_path.c_str(), m_pathFlat.c_str(), fs::copy_options::overwrite_existing);
        fs::create_directory(m_pathFlat.c_str());
    }
    catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
        return false; 
    }
    return true; 
}

bool LatexFile::backToTheRoots()
{
    namespace fs = boost::filesystem;
    string line("");
    string filename(m_pathFlat+'/'+m_filename);
    string path; 
    string newPath; 
    const string key1("\\includegraphics");
    const string key2("\\bibliography{");
    const string key3("%");
    size_t found1;
    size_t found2;
    size_t pos1;
    size_t pos2;
    size_t pos3;


    if (fs::exists(m_pathFlat+'/'+m_filename+"_temp"))
        fs::remove(m_pathFlat+'/'+m_filename+"_temp");
    fs::copy_file(m_pathFlat+'/'+m_filename, m_pathFlat+'/'+m_filename+"_temp");
    fs::remove(m_pathFlat+'/'+m_filename);
    filename = m_pathFlat+'/'+m_filename+"_temp";

    ifstream in(filename);
    if (!in)
    {
        cout << "could not open " << filename << " to bring all its figures to the root" <<endl;
        return false; 
    }
    ofstream out(m_pathFlat+'/'+m_filename); 
    if (!out)
    {
        cout << "could not open " << m_pathFlat+'/'+m_filename << " to shorten paths " << filename <<endl;
        return false; 
    }
 
    if (m_verbose)
        cout << "Copying figures in the root directory and shortening paths" << endl; 




    while(getline(in,line))
    {
        found1 = line.find(key1, 0);
        found2 = line.find(key2, 0);
        if ((found1 != string::npos) || (found2 != string::npos))
        {
            // if (m_verbose)
            //     cout << "Potential candidate : " << line << endl;
            found1 = line.substr(0, min(found1, found2)).find(key3, 0);
            if (found1 == string::npos)
            {
                pos1 = line.find_first_of('{');
                pos2 = line.find_first_of('}');
                path = line.substr(pos1+1, (pos2-pos1-1));
                pos3 = line.find_last_of('/');
                newPath = line.substr(pos3+1, pos2-pos3-1);
                if (m_verbose)
                    cout << "Replacing " << path << " by " << newPath << " : line " << line ;     
                line = line.substr(0,pos1+1) + newPath + line.substr(pos2, line.size());
                if (m_verbose)
                {
                    cout << " becomes : " << line << endl;
                    cout << " copying " << m_path+'/'+path << " into " << m_pathFlat+'/'+newPath << endl;
                }
                fs::copy_file(m_path+'/'+path, m_pathFlat+'/'+newPath, fs::copy_options::overwrite_existing);
            }
        }
        out << line << endl;
    }
    fs::remove(m_pathFlat+'/'+m_filename+"_temp");

    return true;
}



// std::string m_filename;
// std::string m_filenameFlat;
// std::string m_path;
// std::string m_pathFlat;
// bool m_imFlat;