, stdout);
 fputs(
"              socket. The socket is used to seed the  random  engine  for  SSL\n"
"              connections. See also the --random-file option.\n"
"\n"
"       -E/--cert <certificate[:password]>\n"
"              (SSL) Tells curl to use the specified certificate file when get-\n"
"              ting a file with HTTPS or FTPS. The certificate must be  in  PEM\n"
"              format.   If  the  optional password isn't specified, it will be\n"
"              queried for on the terminal. Note that  this  option  assumes  a\n"
, stdout);
 fputs(
"              \"certificate\"  file that is the private key and the private cer-\n"
"              tificate concatenated! See --cert  and  --key  to  specify  them\n"
"              independently.\n"
"\n"
"              If  curl  is  built against the NSS SSL library then this option\n"
"              can tell curl the nickname of the certificate to use within  the\n"
"              NSS  database defined by the environment variable SSL_DIR (or by\n"
, stdout);
 fputs(
