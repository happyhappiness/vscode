puts(
"  ... you can then in a second connect to that (or another) site, use the\n"
"  cookies from the 'headers' file like:\n"
"\n"
"        curl -b headers www.example.com\n"
"\n"
"  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
"  you can make curl follow a location: (which often is used in combination\n"
"  with cookies). So that if a site sends cookies and a location, you can\n"
"  use a non-existing file to trigger the cookie awareness like:\n"
"\n"
"        curl -L -b empty.txt www.example.com\n"
"\n"
);