fputs(
"              remote  TLS  server.   You can use options --tlsv1.0, --tlsv1.1,\n"
"              and --tlsv1.2 to control the TLS version more precisely (if  the\n"
"              SSL backend in use supports such a level of control).\n"
"\n"
"       -2, --sslv2\n"
"              (SSL)  Forces  curl to use SSL version 2 when negotiating with a\n"
"              remote SSL server. Sometimes curl is built  without  SSLv2  sup-\n"
"              port. SSLv2 is widely considered insecure (see RFC 6176).\n"
"\n"
"       -3, --sslv3\n"
, stdout);