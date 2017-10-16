 "   Note that using FTPS:// as prefix is the \"implicit\" way as described in the\n"
 "   standards while the recommended \"explicit\" way is done by using FTP:// and\n"
 "   the --ftp-ssl option.\n"
 "\n"
 " HTTP\n"
 "\n"
-, stdout);
- fputs(
 "   Curl also supports user and password in HTTP URLs, thus you can pick a file\n"
 "   like:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl http://name:passwd@machine.domain/full/path/to/file\n"
 "\n"
 "   or specify user and password separately like in\n"
 "\n"
 "        curl -u name:passwd http://machine.domain/full/path/to/file\n"
 "\n"
 "   HTTP offers many different methods of authentication and curl supports\n"
 "   several: Basic, Digest, NTLM and Negotiate. Without telling which method to\n"
-, stdout);
- fputs(
 "   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
 "   ones out of the ones that the server accepts for the given URL, by using\n"
+, stdout);
+ fputs(
 "   --anyauth.\n"
 "\n"
 "   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
 "   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
 "   during such circumstances.\n"
 "\n"
 " HTTPS\n"
 "\n"
 "   Probably most commonly used with private certificates, as explained below.\n"
 "\n"
 "PROXY\n"
 "\n"
-, stdout);
- fputs(
 " Get an ftp file using a proxy named my-proxy that uses port 888:\n"
 "\n"
 "        curl -x my-proxy:888 ftp://ftp.leachsite.com/README\n"
 "\n"
 " Get a file from a HTTP server that requires user and password, using the\n"
+, stdout);
+ fputs(
 " same proxy as above:\n"
 "\n"
 "        curl -u user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
 " Some proxies require special authentication. Specify by using -U as above:\n"
 "\n"
 "        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
-, stdout);
- fputs(
 " curl also supports SOCKS4 and SOCKS5 proxies with --socks4 and --socks5.\n"
 "\n"
 " See also the environment variables Curl support that offer further proxy\n"
 " control.\n"
 "\n"
 "RANGES\n"
 "\n"
 "  With HTTP 1.1 byte-ranges were introduced. Using this, a client can request\n"
+, stdout);
+ fputs(
 "  to get only one or more subparts of a specified document. Curl supports\n"
 "  this with the -r flag.\n"
 "\n"
 "  Get the first 100 bytes of a document:\n"
 "\n"
 "        curl -r 0-99 http://www.get.this/\n"
 "\n"
 "  Get the last 500 bytes of a document:\n"
 "\n"
-, stdout);
- fputs(
 "        curl -r -500 http://www.get.this/\n"
 "\n"
 "  Curl also supports simple ranges for FTP files as well. Then you can only\n"
 "  specify start and stop position.\n"
 "\n"
 "  Get the first 100 bytes of a document using FTP:\n"
