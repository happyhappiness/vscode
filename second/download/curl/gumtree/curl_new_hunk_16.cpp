"        http://curl.haxx.se\n"
"\n"
"SIMPLE USAGE\n"
"\n"
"  Get the main page from netscape's web-server:\n"
"\n"
"        curl http://www.netscape.com/\n"
"\n"
"  Get the README file the user's home directory at funet's ftp-server:\n"
"\n"
"        curl ftp://ftp.funet.fi/README\n"
"\n"
, stdout);
 fputs(
"  Get a web page from a server using port 8000:\n"
"\n"
"        curl http://www.weirdserver.com:8000/\n"
"\n"
"  Get a list of a directory of an FTP site:\n"
"\n"
"        curl ftp://cool.haxx.se/\n"
"\n"
"  Get a gopher document from funet's gopher server:\n"
"\n"
"        curl gopher://gopher.funet.fi\n"
"\n"
"  Get the definition of curl from a dictionary:\n"
"\n"
"        curl dict://dict.org/m:curl\n"
"\n"
"  Fetch two documents at once:\n"
"\n"
"        curl ftp://cool.haxx.se/ http://www.weirdserver.com:8000/\n"
"\n"
"DOWNLOAD TO A FILE\n"
"\n"
, stdout);
 fputs(
"  Get a web page and store in a local file:\n"
"\n"
"        curl -o thatpage.html http://www.netscape.com/\n"
"\n"
"  Get a web page and store in a local file, make the local file get the name\n"
"  of the remote document (if no file name part is specified in the URL, this\n"
"  will fail):\n"
"\n"
"        curl -O http://www.netscape.com/index.html\n"
"\n"
"  Fetch two files and store them with their remote names:\n"
"\n"
"        curl -O www.haxx.se/index.html -O curl.haxx.se/download.html\n"
"\n"
"USING PASSWORDS\n"
"\n"
" FTP\n"
"\n"
, stdout);
 fputs(
"   To ftp files using name+passwd, include them in the URL like:\n"
"\n"
"        curl ftp://name:passwd@machine.domain:port/full/path/to/file\n"
"\n"
"   or specify them with the -u flag like\n"
"\n"
"        curl -u name:passwd ftp://machine.domain:port/full/path/to/file\n"
"\n"
" HTTP\n"
"\n"
"   The HTTP URL doesn't support user and password in the URL string. Curl\n"
"   does support that anyway to provide a ftp-style interface and thus you can\n"
"   pick a file like:\n"
"\n"
"        curl http://name:passwd@machine.domain/full/path/to/file\n"
"\n"
, stdout);
 fputs(
"   or specify user and password separately like in\n"
"\n"
"        curl -u name:passwd http://machine.domain/full/path/to/file\n"
"\n"
"   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
"   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
"   during such circumstances.\n"
"\n"
" HTTPS\n"
"\n"
"   Probably most commonly used with private certificates, as explained below.\n"
"\n"
" GOPHER\n"
"\n"
"   Curl features no password support for gopher.\n"
"\n"
"PROXY\n"
"\n"
, stdout);
 fputs(
" Get an ftp file using a proxy named my-proxy that uses port 888:\n"
"\n"
"        curl -x my-proxy:888 ftp://ftp.leachsite.com/README\n"
"\n"
" Get a file from a HTTP server that requires user and password, using the\n"
" same proxy as above:\n"
"\n"
"        curl -u user:passwd -x my-proxy:888 http://www.get.this/\n"
"\n"
" Some proxies require special authentication. Specify by using -U as above:\n"
"\n"
"        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
"\n"
, stdout);
 fputs(
" See also the environment variables Curl support that offer further proxy\n"
" control.\n"
"\n"
"RANGES\n"
"\n"
"  With HTTP 1.1 byte-ranges were introduced. Using this, a client can request\n"
