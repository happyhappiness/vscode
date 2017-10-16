"              col. The certificate must be in PKCS#12 format if  using  Secure\n"
, stdout);
 fputs(
"              Transport,  or  PEM  format  if  using any other engine.  If the\n"
"              optional password isn't specified, it will be queried for on the\n"
"              terminal.  Note  that  this  option assumes a \"certificate\" file\n"
"              that is the private key and the client certificate concatenated!\n"
"              See --cert and --key to specify them independently.\n"
"\n"
"              If  curl  is  built against the NSS SSL library then this option\n"
, stdout);
 fputs(
"              can tell curl the nickname of the certificate to use within  the\n"
"              NSS  database defined by the environment variable SSL_DIR (or by\n"
