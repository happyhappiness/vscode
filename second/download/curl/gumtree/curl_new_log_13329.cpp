fputs(
"  file contents.  In the above command, curl will parse the header and store\n"
"  the cookies received from www.example.com.  curl will send to the server the\n"
"  stored cookies which match the request as it follows the location.  The\n"
"  file \"empty.txt\" may be a nonexistent file.\n"
"\n"
"  To read and write cookies from a netscape cookie file, you can set both -b\n"
"  and -c to use the same file:\n"
"\n"
"        curl -b cookies.txt -c cookies.txt www.example.com\n"
"\n"
"PROGRESS METER\n"
"\n"
, stdout);