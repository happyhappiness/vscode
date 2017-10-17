fputs(
"  ... you can then in a second connect to that (or another) site, use the\n"
"  cookies from the 'headers' file like:\n"
"\n"
"        curl -b headers www.example.com\n"
"\n"
"  While saving headers to a file is a working way to store cookies, it is\n"
"  however error-prone and not the preferred way to do this. Instead, make curl\n"
"  save the incoming cookies using the well-known netscape cookie format like\n"
"  this:\n"
"\n"
"        curl -c cookies.txt www.example.com\n"
"\n"
, stdout);