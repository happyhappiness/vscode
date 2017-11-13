fputs(
"              HTTP/2 without HTTP/1.1 Upgrade.  It  requires  prior  knowledge\n"
"              that  the  server  supports HTTP/2 straight away. HTTPS requests\n"
"              will still do HTTP/2 the standard way with  negotiated  protocol\n"
"              version in the TLS handshake.\n"
"\n"
"              HTTP/2  support  in  general  also  requires that the underlying\n"
"              libcurl was built to support it. (Added in 7.49.0)\n"
"\n"
"       --no-npn\n"
, stdout);