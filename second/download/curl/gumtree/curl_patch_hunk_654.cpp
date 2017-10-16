 , stdout);
  fputs(
 "              url_effective  The URL that was fetched last. This is most mean-\n"
 "                             ingful if you've told curl  to  follow  location:\n"
 "                             headers.\n"
 "\n"
+"              filename_effective\n"
+"                             The  ultimate  filename  that curl writes out to.\n"
+"                             This is only meaningful if curl is told to  write\n"
+"                             to  a  file  with  the  --remote-name or --output\n"
+, stdout);
+ fputs(
+"                             option. It's most useful in combination with  the\n"
+"                             --remote-header-name option. (Added in 7.25.1)\n"
+"\n"
 "              http_code      The numerical response code that was found in the\n"
 "                             last retrieved HTTP(S)  or  FTP(s)  transfer.  In\n"
 "                             7.18.2  the alias response_code was added to show\n"
 "                             the same info.\n"
 "\n"
 , stdout);
