  fputs(
 "              If this option is used twice, the second will  again  switch  on\n"
 "              use of the session cache.\n"
 "\n"
 "       --ntlm (HTTP)  Enables  NTLM  authentication.  The  NTLM authentication\n"
 "              method was designed by Microsoft and is used by IIS web servers.\n"
-"              It is a proprietary protocol, reversed engineered by clever peo‐\n"
+"              It is a proprietary protocol, reversed engineered by clever peo-\n"
 "              ple and implemented in curl based on their efforts. This kind of\n"
 , stdout);
  fputs(
 "              behavior  should  not be endorsed, you should encourage everyone\n"
-"              who uses NTLM to switch to a public and  documented  authentica‐\n"
+"              who uses NTLM to switch to a public and  documented  authentica-\n"
 "              tion method instead. Such as Digest.\n"
 "\n"
 "              If  you  want to enable NTLM for your proxy authentication, then\n"
 "              use --proxy-ntlm.\n"
 "\n"
-"              This option requires that the library was built  with  SSL  sup‐\n"
+"              This option requires that the library was built  with  SSL  sup-\n"
 "              port. Use -V/--version to see if your curl supports NTLM.\n"
 "\n"
 , stdout);
  fputs(
 "              If  this option is used several times, the following occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -o/--output <file>\n"
 "              Write output to <file> instead of stdout. If you are using {} or\n"
-"              []  to  fetch  multiple documents, you can use ’#’ followed by a\n"
+"              []  to  fetch  multiple documents, you can use '#' followed by a\n"
 "              number in the <file> specifier. That variable will  be  replaced\n"
 "              with the current string for the URL being fetched. Like in:\n"
 "\n"
 , stdout);
  fputs(
 "                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
