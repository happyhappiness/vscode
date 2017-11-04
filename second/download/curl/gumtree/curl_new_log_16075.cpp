fputs(
"              remote  SSL  server.  Sometimes curl is built without SSLv2 sup-\n"
"              port. SSLv2 is widely considered insecure (see RFC 6176).\n"
"\n"
"              See also --http1.1 and --http2. -2, --sslv2  requires  that  the\n"
"              underlying  libcurl  was built to support TLS. This option over-\n"
"              rides -3, --sslv3 and -1, --tlsv1 and --tlsv1.1 and --tlsv1.2.\n"
"\n"
"       -3, --sslv3\n"
"              (SSL) Forces curl to use SSL version 3 when negotiating  with  a\n"
, stdout);