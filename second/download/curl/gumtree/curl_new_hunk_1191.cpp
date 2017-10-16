"\n"
"          500-700,600-799\n"
"                    specifies 300 bytes from offset 500(H)\n"
"\n"
"          100-199,500-599\n"
"                    specifies two separate 100 bytes ranges(*)(H)\n"
);
 puts(
"\n"
"     (*) = NOTE that this will cause the server to reply with a\n"
"     multipart response!\n"
"\n"
"     You should also be aware that many HTTP/1.1 servers do not\n"
"     have this feature enabled, so that when you attempt to get a\n"
