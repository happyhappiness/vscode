#include <iostream>
#include <fstream.h>
#include <string>
#include <regex>

using namespace std;

int main()
{

    ///get intial diff file
    string patchName = "~/Desktop/info/code/cpp/8743-8742.diff";
    ifstream patch(patchName);
    string line;
    if(patch.is_open())
    {
        while(!patch.eof())
        {
            cout << "Startt reading ..." << endl;
            patch.getline(line);
            cout << line << endl;
        }
    }

    ///retrieve log lines

    ///retrieve add lines

    ///retrieve delete lines

    ///retrieve move lines

    ///retrieve content change lines
}
