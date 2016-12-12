#include <iostream>
#include <fstream>
#include <string.h>
#include <regex.h>

using namespace std;


 /* init regex with given pattern
    @param pattern,
    @param reg

    @return bool
  */
bool initRegex(const char* pattern, regex_t& reg)
{
    const int EBUFLEN = 100;
    char errbuf[EBUFLEN];
    int err;

    /* init with given pattern and regex */
    err = regcomp(&reg, pattern, REG_EXTENDED);

    /* deal with error */
    if (err) {
        regerror(err, &reg, errbuf, EBUFLEN);
        printf("error: regcomp: %s\n", errbuf);
        return false;
    }
    printf("Total has subexpression: %ld\n", reg.re_nsub);

    return true;
}

 /* execute regex match with given regex and instring
    @param regex,
    @param in,
    @param BUFLEN

    @return void
  */
void exeRegex(const regex_t& reg, const char* in, const int BUFLEN) 
{
    const int SUBSLEN = 20;  
    char errbuf[BUFLEN];
    regmatch_t subs[SUBSLEN];   
    char matched[BUFLEN]; 

    int err = regexec(&reg, in, (size_t) SUBSLEN, subs, 0);

    // deal with error
    if (err == REG_NOMATCH)
    {
        return;
    } 
    // print other kinds of error
    else if(err)
    {
        regerror(err, &reg, errbuf, sizeof(errbuf));
        printf("error: regexec: %s\n", errbuf);
        return;
    }

    // deal with matched subString
    int len, i;
    for (i = 0; i <= reg.re_nsub; i++) {
        len = subs[i].rm_eo - subs[i].rm_so;
        // store the ith substring start: rm_so, end: rm_eo
        memcpy (matched, in + subs[i].rm_so, len);
        matched[len] = '\0';
        printf("%s\n", matched);
    }

}

int main()
{

    ///get intial diff file
    const char* patchName = "/usr/code/cpp/test.diff";
    const int LINELEN = 100;
    fstream patch;
    patch.open(patchName, ios_base::in);

    //string line;
    char line[LINELEN];
    if(patch.is_open())
    {
        //init regex
        const char* pattern = "^(-+).*";
        regex_t regex;
        if(!initRegex(pattern, regex))
            return -1;
        cout << "init regex successfully ..." << endl;

        while(patch.getline(line, LINELEN))
        {
            //match 
            //exeRegex(regex, line, LINELEN);
            cout << line << endl;
        }

        //release regex
        regfree(&regex);
    }

    cout << "process over ..." << endl;

    // //retrieve log lines

    // //retrieve add lines

    // //retrieve delete lines

    // //retrieve move lines

    // //retriesve content change lines
}
