"       --pinnedpubkey <pinned public key (hashes)>\n"
"              (SSL) Tells curl to  use  the  specified  public  key  file  (or\n"
"              hashes)  to  verify the peer. This can be a path to a file which\n"
"              contains a single public key in PEM or DER format, or any number\n"
, stdout);
 fputs(
"              of base64 encoded sha256 hashes preceded by 'sha256//' and sepa-\n"
"              rated by ';'\n"
"\n"
"              When negotiating a TLS or SSL connection,  the  server  sends  a\n"
"              certificate  indicating  its identity. A public key is extracted\n"
"              from this certificate and if it does not exactly match the  pub-\n"
"              lic  key provided to this option, curl will abort the connection\n"
"              before sending or receiving any data.\n"
