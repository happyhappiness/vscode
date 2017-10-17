fputs(
"  If there's a \"normal\" post, you use -d to post. -d takes a full \"post\n"
"  string\", which is in the format\n"
"\n"
"        <variable1>=<data1>&<variable2>=<data2>&...\n"
"\n"
"  The 'variable' names are the names set with \"name=\" in the <input> tags, and\n"
"  the data is the contents you want to fill in for the inputs. The data *must*\n"
"  be properly URL encoded. That means you replace space with + and that you\n"
"  replace weird letters with %XX where XX is the hexadecimal representation of\n"
, stdout);