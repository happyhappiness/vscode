"\n"
"       -D/--dump-header <file>\n"
"              Write the protocol headers to the specified file.\n"
"\n"
"              This  option  is handy to use when you want to store the headers\n"
"              that a HTTP site sends to you. Cookies from  the  headers  could\n"
"              then   be  read  in  a  second  curl  invocation  by  using  the\n"
, stdout);
 fputs(
"              -b/--cookie option! The -c/--cookie-jar option is however a bet-\n"
"              ter way to store cookies.\n"
"\n"
"              When  used  in FTP, the FTP server response lines are considered\n"
"              being \"headers\" and thus are saved there.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -e/--referer <URL>\n"
"              (HTTP)  Sends the \"Referer Page\" information to the HTTP server.\n"
