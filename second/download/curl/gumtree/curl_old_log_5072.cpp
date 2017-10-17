fputs(
"       --libcurl <file>\n"
"              Append  this  option  to any ordinary curl command line, and you\n"
"              will get a libcurl-using source code written to  the  file  that\n"
"              does the equivalent of what your command-line operation does!\n"
"\n"
"              NOTE:  this does not properly support -F and the sending of mul-\n"
"              tipart formposts, so in those cases the output program  will  be\n"
"              missing necessary calls to curl_formadd(3), and possibly more.\n"
"\n"
, stdout);