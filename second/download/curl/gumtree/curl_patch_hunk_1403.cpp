 "\n"
 "  Get a web page and store in a local file:\n"
 "\n"
 "        curl -o thatpage.html http://www.netscape.com/\n"
 "\n"
 "  Get a web page and store in a local file, make the local file get the name\n"
-);
- puts(
 "  of the remote document (if no file name part is specified in the URL, this\n"
 "  will fail):\n"
 "\n"
+);
+ puts(
 "        curl -O http://www.netscape.com/index.html\n"
 "\n"
 "  Fetch two files and store them with their remote names:\n"
 "\n"
 "        curl -O www.haxx.se/index.html -O curl.haxx.se/download.html\n"
 "\n"
