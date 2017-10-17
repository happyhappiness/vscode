fputs(
"  Curl also has the ability to use previously received cookies in following\n"
"  sessions. If you get cookies from a server and store them in a file in a\n"
"  manner similar to:\n"
"\n"
"        curl --dump-header headers www.example.com\n"
"\n"
"  ... you can then in a second connect to that (or another) site, use the\n"
"  cookies from the 'headers' file like:\n"
"\n"
"        curl -b headers www.example.com\n"
"\n"
"  While saving headers to a file is a working way to store cookies, it is\n"
, stdout);