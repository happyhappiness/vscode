fputs(
"        curl -c cookies.txt www.example.com\n"
"\n"
"  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
"  you can make curl follow a location: (which often is used in combination\n"
"  with cookies). So that if a site sends cookies and a location, you can\n"
"  use a non-existing file to trigger the cookie awareness like:\n"
"\n"
"        curl -L -b empty.txt www.example.com\n"
"\n"
"  The file to read cookies from must be formatted using plain HTTP headers OR\n"
, stdout);