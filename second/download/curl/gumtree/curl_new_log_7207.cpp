fputs(
"              them with \":\" (e.g.  \"path1:path2:path3\"). The certificates must\n"
"              be  in  PEM  format,  and  if curl is built against OpenSSL, the\n"
"              directory must have been processed using  the  c_rehash  utility\n"
"              supplied  with OpenSSL. Using --capath can allow OpenSSL-powered\n"
"              curl to make SSL-connections much more  efficiently  than  using\n"
"              --cacert if the --cacert file contains many CA certificates.\n"
"\n"
, stdout);