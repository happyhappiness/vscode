fputs(
"  For HTTP, you can get the header information (the same as -I would show)\n"
"  shown before the data by using -i/--include. Curl understands the\n"
"  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
"  will then store the headers in the specified file.\n"
"\n"
"  Store the HTTP headers in a separate file (headers.txt in the example):\n"
"\n"
"        curl --dump-header headers.txt curl.haxx.se\n"
"\n"
"  Note that headers stored in a separate file can be very useful at a later\n"
, stdout);