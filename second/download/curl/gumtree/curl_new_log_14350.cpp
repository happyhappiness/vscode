fputs(
"              -0, --http1.0 and --http2-prior-knowledge. Added in 7.33.0.\n"
"\n"
"       --ignore-content-length\n"
"              (FTP HTTP) For HTTP, Ignore the Content-Length header.  This  is\n"
"              particularly  useful  for servers running Apache 1.x, which will\n"
"              report incorrect Content-Length for files larger  than  2  giga-\n"
"              bytes.\n"
"\n"
"              For  FTP (since 7.46.0), skip the RETR command to figure out the\n"
"              size before downloading a file.\n"
"\n"
, stdout);