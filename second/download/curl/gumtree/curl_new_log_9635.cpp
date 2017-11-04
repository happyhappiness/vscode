fputs(
"  Dig out all the <input> tags in the form that you want to fill in. (There's\n"
"  a perl program called formfind.pl on the curl site that helps with this).\n"
"\n"
"  If there's a \"normal\" post, you use -d to post. -d takes a full \"post\n"
"  string\", which is in the format\n"
"\n"
"        <variable1>=<data1>&<variable2>=<data2>&...\n"
"\n"
"  The 'variable' names are the names set with \"name=\" in the <input> tags, and\n"
"  the data is the contents you want to fill in for the inputs. The data *must*\n"
, stdout);