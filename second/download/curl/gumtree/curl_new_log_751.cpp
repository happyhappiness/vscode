fputs(
"                        specifies   two   separate   100    bytes\n"
"                        ranges(*)(H)\n"
"\n"
"       (*) = NOTE that this will cause the server to reply with a\n"
"       multipart response!\n"
"\n"
"       You should also be aware that many HTTP/1.1 servers do not\n"
"       have this feature enabled, so that when you attempt to get\n"
"       a range, you'll instead get the whole document.\n"
"\n"
"       FTP range downloads only support the simple syntax 'start-\n"
, stdout);