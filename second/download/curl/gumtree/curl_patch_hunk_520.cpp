 , stdout);
  fputs(
 "              socket. The socket is used to seed the  random  engine  for  SSL\n"
 "              connections. See also the --random-file option.\n"
 "\n"
 "       -E/--cert <certificate[:password]>\n"
-"              (SSL) Tells curl to use the specified certificate file when get-\n"
-"              ting a file with HTTPS or FTPS. The certificate must be  in  PEM\n"
-"              format.   If  the  optional password isn't specified, it will be\n"
-"              queried for on the terminal. Note that  this  option  assumes  a\n"
+"              (SSL)  Tells  curl  to use the specified client certificate file\n"
+"              when getting a file with HTTPS, FTPS or another SSL-based proto-\n"
+"              col.  The  certificate  must  be in PEM format.  If the optional\n"
+"              password isn't specified, it will be queried for on  the  termi-\n"
 , stdout);
  fputs(
-"              \"certificate\"  file that is the private key and the private cer-\n"
-"              tificate concatenated! See --cert  and  --key  to  specify  them\n"
-"              independently.\n"
+"              nal.  Note that this option assumes a \"certificate\" file that is\n"
+"              the private key and the private  certificate  concatenated!  See\n"
+"              --cert and --key to specify them independently.\n"
 "\n"
 "              If  curl  is  built against the NSS SSL library then this option\n"
 "              can tell curl the nickname of the certificate to use within  the\n"
 "              NSS  database defined by the environment variable SSL_DIR (or by\n"
 , stdout);
  fputs(
