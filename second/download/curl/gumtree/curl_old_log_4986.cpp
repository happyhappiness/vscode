fputs(
"        ftp://ftp.numericals.com/file[001-100].txt    (with leading zeros)\n"
"        ftp://ftp.letters.com/file[a-z].txt\n"
"\n"
"       No nesting of the sequences is supported at the moment, but you can use\n"
"       several ones next to each other:\n"
"\n"
"        http://any.org/archive[1996-1999]/vol[1-4]/part{a,b,c}.html\n"
"\n"
"       You  can  specify  any amount of URLs on the command line. They will be\n"
"       fetched in a sequential manner in the specified order.\n"
"\n"
, stdout);