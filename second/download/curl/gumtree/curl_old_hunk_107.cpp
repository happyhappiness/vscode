"\n"
"        curl -b \"name=Daniel\" www.sillypage.com\n"
"\n"
"  Curl also has the ability to use previously received cookies in following\n"
"  sessions. If you get cookies from a server and store them in a file in a\n"
"  manner similar to:\n"
);
 puts(
"\n"
"        curl --dump-header headers www.example.com\n"
"\n"
"  ... you can then in a second connect to that (or another) site, use the\n"
"  cookies from the 'headers' file like:\n"
"\n"
