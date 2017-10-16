fputs(
"              directory  must  have  been processed using the c_rehash utility\n"
"              supplied with openssl. Using --capath can  allow  curl  to  make\n"
"              SSL-connections much more efficiently than using --cacert if the\n"
"              --cacert file contains many CA certificates.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -f/--fail\n"
"              (HTTP)  Fail  silently (no output at all) on server errors. This\n"
, stdout);