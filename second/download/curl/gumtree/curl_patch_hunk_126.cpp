 "  as netscape's cookie file. Curl will determine what kind it is based on the\n"
 , stdout);
  fputs(
 "  file contents.  In the above command, curl will parse the header and store\n"
 "  the cookies received from www.example.com.  curl will send to the server the\n"
 "  stored cookies which match the request as it follows the location.  The\n"
-"  file \"empty.txt\" may be a non-existant file.\n"
+"  file \"empty.txt\" may be a nonexistent file.\n"
 "\n"
 "  Alas, to both read and write cookies from a netscape cookie file, you can\n"
 "  set both -b and -c to use the same file:\n"
 "\n"
 "        curl -b cookies.txt -c cookies.txt www.example.com\n"
 "\n"
