"  receives in order to let the user see all client-server interaction.\n"
"\n"
"        curl -v ftp://ftp.upload.com/\n"
"\n"
"DETAILED INFORMATION\n"
"\n"
);
 puts(
"  Different protocols provide different ways of getting detailed information\n"
"  about specific files/documents. To get curl to show detailed information\n"
"  about a single file, you should use -I/--head option. It displays all\n"
"  available info on a single file for HTTP and FTP. The HTTP information is a\n"
"  lot more extensive.\n"
"\n"
"  For HTTP, you can get the header information (the same as -I would show)\n"
"  shown before the data by using -i/--include. Curl understands the\n"
);
 puts(
"  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
"  will then store the headers in the specified file.\n"
"\n"
"  Store the HTTP headers in a separate file:\n"
"\n"
"        curl --dump-header headers.txt curl.haxx.se\n"
