fputs(
" (*1) = This requires that the FTP server supports the non-standard command\n"
"        SIZE. If it doesn't, curl will say so.\n"
"\n"
" (*2) = This requires that the web server supports at least HTTP/1.1. If it\n"
"        doesn't, curl will say so.\n"
"\n"
"TIME CONDITIONS\n"
"\n"
" HTTP allows a client to specify a time condition for the document it\n"
" requests. It is If-Modified-Since or If-Unmodified-Since. Curl allows you to\n"
" specify them with the -z/--time-cond flag.\n"
"\n"
, stdout);