 " HTTP\n"
 "\n"
 "  Upload all data on stdin to a specified HTTP site:\n"
 "\n"
 "        curl -T - http://www.upload.com/myfile\n"
 "\n"
+, stdout);
+ fputs(
 "  Note that the HTTP server must have been configured to accept PUT before\n"
 "  this can be done successfully.\n"
 "\n"
-, stdout);
- fputs(
 "  For other ways to do HTTP data upload, see the POST section below.\n"
 "\n"
 "VERBOSE / DEBUG\n"
 "\n"
 "  If curl fails where it isn't supposed to, if the servers don't let you in,\n"
 "  if you can't understand the responses: use the -v flag to get verbose\n"
 "  fetching. Curl will output lots of info and what it sends and receives in\n"
 "  order to let the user see all client-server interaction (but it won't show\n"
+, stdout);
+ fputs(
 "  you the actual data).\n"
 "\n"
 "        curl -v ftp://ftp.upload.com/\n"
 "\n"
-, stdout);
- fputs(
 "  To get even more details and information on what curl does, try using the\n"
 "  --trace or --trace-ascii options with a given file name to log to, like\n"
 "  this:\n"
 "\n"
 "        curl --trace trace.txt www.haxx.se\n"
 "\n"
 "\n"
 "DETAILED INFORMATION\n"
 "\n"
 "  Different protocols provide different ways of getting detailed information\n"
 "  about specific files/documents. To get curl to show detailed information\n"
-"  about a single file, you should use -I/--head option. It displays all\n"
 , stdout);
  fputs(
+"  about a single file, you should use -I/--head option. It displays all\n"
 "  available info on a single file for HTTP and FTP. The HTTP information is a\n"
 "  lot more extensive.\n"
 "\n"
 "  For HTTP, you can get the header information (the same as -I would show)\n"
 "  shown before the data by using -i/--include. Curl understands the\n"
 "  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
 "  will then store the headers in the specified file.\n"
 "\n"
-"  Store the HTTP headers in a separate file (headers.txt in the example):\n"
-"\n"
 , stdout);
  fputs(
+"  Store the HTTP headers in a separate file (headers.txt in the example):\n"
+"\n"
 "        curl --dump-header headers.txt curl.haxx.se\n"
 "\n"
 "  Note that headers stored in a separate file can be very useful at a later\n"
 "  time if you want curl to use cookies sent by the server. More about that in\n"
 "  the cookies section.\n"
 "\n"
