fputs(
"  with cookies). So that if a site sends cookies and a location, you can\n"
"  use a non-existing file to trigger the cookie awareness like:\n"
"\n"
"        curl -L -b empty.txt www.example.com\n"
"\n"
"  The file to read cookies from must be formatted using plain HTTP headers OR\n"
"  as netscape's cookie file. Curl will determine what kind it is based on the\n"
"  file contents.  In the above command, curl will parse the header and store\n"
"  the cookies received from www.example.com.  curl will send to the server the\n"
, stdout);