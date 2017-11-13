fputs(
"              See  also  --no-alpn  and  --http2.  --no-npn  requires that the\n"
"              underlying libcurl was built to support TLS. Added in 7.36.0.\n"
"\n"
"       --no-sessionid\n"
"              (TLS) Disable curl's use of SSL session-ID caching.  By  default\n"
"              all  transfers are done using the cache. Note that while nothing\n"
"              should ever get hurt by attempting  to  reuse  SSL  session-IDs,\n"
"              there seem to be broken SSL implementations in the wild that may\n"
, stdout);