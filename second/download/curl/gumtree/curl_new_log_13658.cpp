fputs(
"              have. For example, if you specify two URLs on the  same  command\n"
"              line, you can use it like this:\n"
"\n"
"                curl -o aa example.com -o bb example.net\n"
"\n"
"              and  the  order  of  the -o options and the URLs doesn't matter,\n"
"              just that the first -o is for the first URL and so  on,  so  the\n"
"              above command line can also be written as\n"
"\n"
"                curl example.com example.net -o aa -o bb\n"
"\n"
, stdout);