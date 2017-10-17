fputs(
"              0-0,-1    specifies the first and last byte only(*)(H)\n"
"\n"
"              500-700,600-799\n"
"                        specifies 300 bytes from offset 500(H)\n"
"\n"
"              100-199,500-599\n"
"                        specifies two separate 100-byte ranges(*)(H)\n"
"\n"
"       (*)  =  NOTE  that this will cause the server to reply with a multipart\n"
"       response!\n"
"\n"
"       Only digit characters (0-9) are valid in the 'start' and 'stop'  fields\n"
, stdout);