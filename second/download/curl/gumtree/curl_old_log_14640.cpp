fputs(
"              This  option  overrides  -0,  --http1.0  and  --http2.  Added in\n"
"              7.33.0.\n"
"\n"
"       --http2-prior-knowledge\n"
"              (HTTP) Tells curl to  issue  its  non-TLS  HTTP  requests  using\n"
"              HTTP/2  without  HTTP/1.1  Upgrade.  It requires prior knowledge\n"
"              that the server supports HTTP/2 straight  away.  HTTPS  requests\n"
"              will  still  do HTTP/2 the standard way with negotiated protocol\n"
"              version in the TLS handshake.\n"
"\n"
, stdout);