fputs(
"              that the server supports HTTP/2 straight  away.  HTTPS  requests\n"
"              will  still  do HTTP/2 the standard way with negotiated protocol\n"
"              version in the TLS handshake.\n"
"\n"
"              --http2-prior-knowledge requires that the underlying libcurl was\n"
"              built to support HTTP/2. This option overrides --http1.1 and -0,\n"
"              --http1.0 and --http2. Added in 7.49.0.\n"
"\n"
"       --http2\n"
"              (HTTP) Tells curl to use HTTP version 2.\n"
"\n"
, stdout);