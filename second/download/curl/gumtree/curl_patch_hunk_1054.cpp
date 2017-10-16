 , stdout);
  fputs(
 "              should  be used in this session if they match. Using this method\n"
 "              also activates the cookie engine which  will  make  curl  record\n"
 "              incoming cookies too, which may be handy if you're using this in\n"
 "              combination with the -L, --location option. The file  format  of\n"
-"              the  file  to  read cookies from should be plain HTTP headers or\n"
-"              the Netscape/Mozilla cookie file format.\n"
+"              the file to read cookies from should be plain HTTP headers (Set-\n"
+"              Cookie style) or the Netscape/Mozilla cookie file format.\n"
 "\n"
 , stdout);
  fputs(
 "              The file specified with -b, --cookie is only used as  input.  No\n"
 "              cookies  will  be written to the file. To store cookies, use the\n"
 "              -c, --cookie-jar option.\n"
