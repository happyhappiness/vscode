fputs(
"              verify the peer. The certificates must be in PEM format, and the\n"
"              directory must have been processed using  the  c_rehash  utility\n"
"              supplied  with  openssl.  Using  --capath can allow curl to make\n"
"              https connections much more efficiently than using  --cacert  if\n"
"              the --cacert file contains many CA certificates.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -f/--fail\n"
, stdout);