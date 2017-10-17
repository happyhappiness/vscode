fputs(
"  While saving headers to a file is a working way to store cookies, it is\n"
"  however error-prone and not the preferred way to do this. Instead, make curl\n"
"  save the incoming cookies using the well-known netscape cookie format like\n"
"  this:\n"
"\n"
"        curl -c cookies.txt www.example.com\n"
"\n"
"  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
"  you can make curl follow a location: (which often is used in combination\n"
, stdout);