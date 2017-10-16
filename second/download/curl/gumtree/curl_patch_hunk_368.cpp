 "              list  of  host names that shouldn't go through any proxy. If set\n"
 , stdout);
  fputs(
 "              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "EXIT CODES\n"
-"       There exists a bunch of different error codes and  their  corresponding\n"
+"       There are a bunch of different  error  codes  and  their  corresponding\n"
 "       error  messages  that  may appear during bad conditions. At the time of\n"
 "       this writing, the exit codes are:\n"
 "\n"
 "       1      Unsupported protocol. This build of curl has no support for this\n"
 "              protocol.\n"
 "\n"
 "       2      Failed to initialize.\n"
 "\n"
-"       3      URL malformat. The syntax was not correct.\n"
+"       3      URL malformed. The syntax was not correct.\n"
 "\n"
 , stdout);
  fputs(
 "       5      Couldn't  resolve  proxy.  The  given  proxy  host  could not be\n"
 "              resolved.\n"
 "\n"
