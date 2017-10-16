"\n"
" Continue downloading a document:\n"
"\n"
"        curl -C - -o file ftp://ftp.server.com/path/file\n"
"\n"
" Continue uploading a document(*1):\n"
, stdout);
 fputs(
"\n"
"        curl -C - -T file ftp://ftp.server.com/path/file\n"
"\n"
" Continue downloading a document from a web server(*2):\n"
"\n"
"        curl -C - -o file http://www.server.com/\n"
