 "        http://curl.haxx.se\n"
 "\n"
 "SIMPLE USAGE\n"
 "\n"
 "  Get the main page from Netscape's web-server:\n"
 "\n"
-, stdout);
- fputs(
 "        curl http://www.netscape.com/\n"
 "\n"
 "  Get the README file the user's home directory at funet's ftp-server:\n"
+, stdout);
+ fputs(
 "\n"
 "        curl ftp://ftp.funet.fi/README\n"
 "\n"
 "  Get a web page from a server using port 8000:\n"
 "\n"
 "        curl http://www.weirdserver.com:8000/\n"
