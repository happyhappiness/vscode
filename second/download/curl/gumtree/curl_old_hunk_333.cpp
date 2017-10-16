"       --basic\n"
"              (HTTP)  Tells curl to use HTTP Basic authentication. This is the\n"
, stdout);
 fputs(
"              default and this option is usually pointless, unless you use  it\n"
"              to  override  a  previously  set  option  that  sets a different\n"
"              authentication method (such as --ntlm,  --digest  and  --negoti-\n"
"              ate).\n"
"\n"
"       --ciphers <list of ciphers>\n"
"              (SSL) Specifies which ciphers to use in the connection. The list\n"
"              of ciphers must be using valid ciphers. Read up  on  SSL  cipher\n"
, stdout);
 fputs(
"              list           details           on           this          URL:\n"
"              http://www.openssl.org/docs/apps/ciphers.html\n"
"\n"
"              NSS ciphers are done differently than OpenSSL  and  GnuTLS.  The\n"
