fputs(
"       Since curl 7.15.1 you can also specify a step counter for  the  ranges,\n"
"       so that you can get every Nth number or letter:\n"
"\n"
"        http://www.numericals.com/file[1-100:10].txt\n"
"        http://www.letters.com/file[a-z:2].txt\n"
"\n"
"       If  you  specify  URL  without protocol:// prefix, curl will attempt to\n"
"       guess what protocol you might want. It will then default  to  HTTP  but\n"
"       try  other  protocols based on often-used host name prefixes. For exam-\n"
, stdout);