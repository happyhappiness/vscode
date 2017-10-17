fputs(
"       --capath <CA certificate directory>\n"
"              (SSL)  Tells  curl to use the specified certificate directory to\n"
"              verify the peer. The certificates must be in PEM format, and  if\n"
"              curl is built against OpenSSL, the directory must have been pro-\n"
"              cessed using the c_rehash utility supplied with  OpenSSL.  Using\n"
"              --capath  can allow OpenSSL-powered curl to make SSL-connections\n"
, stdout);