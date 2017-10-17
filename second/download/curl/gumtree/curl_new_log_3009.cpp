fputs(
"       Only digit characters (0-9) are valid in ’start’ and  ’stop’  of  range\n"
"       syntax  ’start-stop’.  If  a non-digit character is given in the range,\n"
"       the server’s response will be indeterminable,  depending  on  different\n"
"       server’s configuration.\n"
"\n"
"       You  should  also  be aware that many HTTP/1.1 servers do not have this\n"
"       feature enabled, so that when  you  attempt  to  get  a  range,  you’ll\n"
"       instead get the whole document.\n"
"\n"
, stdout);