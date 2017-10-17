fputs(
"       --capath <CA certificate directory>\n"
"              (HTTPS) Tells curl to use the specified certificate\n"
"              directory to verify the peer. The certificates must\n"
"              be  in PEM format, and the directory must have been\n"
"              processed using the c_rehash utility supplied  with\n"
"              openssl.  Using  --capath  can  allow  curl to make\n"
"              https connections much more efficiently than  using\n"
, stdout);