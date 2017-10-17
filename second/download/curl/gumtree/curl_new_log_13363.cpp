fputs(
"              contains a single public key in PEM or DER format, or any number\n"
"              of base64 encoded sha256 hashes preceded by 'sha256//' and sepa-\n"
"              rated by ';'\n"
"\n"
"              When negotiating a TLS or SSL connection,  the  server  sends  a\n"
"              certificate  indicating  its identity. A public key is extracted\n"
"              from this certificate and if it does not exactly match the  pub-\n"
, stdout);