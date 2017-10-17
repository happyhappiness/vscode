fputs(
"                        specifies 300 bytes from offset 500(H)\n"
"\n"
"              100-199,500-599\n"
"                        specifies two separate 100 bytes ranges(*)(H)\n"
"\n"
"       (*)  =  NOTE  that this will cause the server to reply with a multipart\n"
"       response!\n"
"\n"
"       You should also be aware that many HTTP/1.1 servers do  not  have  this\n"
"       feature  enabled,  so  that  when  you  attempt  to get a range, you'll\n"
"       instead get the whole document.\n"
"\n"
, stdout);