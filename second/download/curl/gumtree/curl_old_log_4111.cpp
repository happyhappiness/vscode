fputs(
"                        specifies two separate 100 bytes ranges(*)(H)\n"
"\n"
"       (*)  =  NOTE  that this will cause the server to reply with a multipart\n"
"       response!\n"
"\n"
"       Only digit characters (0-9) are valid in 'start' and  'stop'  of  range\n"
"       syntax  'start-stop'.  If  a non-digit character is given in the range,\n"
"       the server's response will be indeterminable,  depending  on  different\n"
"       server's configuration.\n"
"\n"
, stdout);