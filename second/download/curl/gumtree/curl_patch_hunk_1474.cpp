 );
  puts(
 " resume on http(s) downloads as well as ftp uploads and downloads.\n"
 "\n"
 " Continue downloading a document:\n"
 "\n"
-"        curl -c -o file ftp://ftp.server.com/path/file\n"
+"        curl -C - -o file ftp://ftp.server.com/path/file\n"
 "\n"
 " Continue uploading a document(*1):\n"
 "\n"
-"        curl -c -T file ftp://ftp.server.com/path/file\n"
+"        curl -C - -T file ftp://ftp.server.com/path/file\n"
 "\n"
 " Continue downloading a document from a web server(*2):\n"
 "\n"
-"        curl -c -o file http://www.server.com/\n"
+"        curl -C - -o file http://www.server.com/\n"
 "\n"
 " (*1) = This requires that the ftp server supports the non-standard command\n"
 "        SIZE. If it doesn't, curl will say so.\n"
 "\n"
 );
  puts(
