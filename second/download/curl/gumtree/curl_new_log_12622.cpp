fputs(
"         ftp://ftp.example.com/file[001-100].txt    (with leading zeros)\n"
"\n"
"         ftp://ftp.example.com/file[a-z].txt\n"
"\n"
"       Nested  sequences  are not supported, but you can use several ones next\n"
"       to each other:\n"
"\n"
"         http://example.com/archive[1996-1999]/vol[1-4]/part{a,b,c}.html\n"
"\n"
"       You can specify any amount of URLs on the command line.  They  will  be\n"
"       fetched in a sequential manner in the specified order.\n"
"\n"
, stdout);