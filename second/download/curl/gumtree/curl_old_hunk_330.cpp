"\n"
"       You  can  specify  any amount of URLs on the command line. They will be\n"
"       fetched in a sequential manner in the specified order.\n"
"\n"
, stdout);
 fputs(
"       Since curl 7.15.1 you can also specify step counter for the ranges,  so\n"
"       that you can get every Nth number or letter:\n"
"        http://www.numericals.com/file[1-100:10].txt\n"
"        http://www.letters.com/file[a-z:2].txt\n"
"\n"
"       If  you  specify  URL  without protocol:// prefix, curl will attempt to\n"
"       guess what protocol you might want. It will then default  to  HTTP  but\n"
"       try  other  protocols based on often-used host name prefixes. For exam-\n"
