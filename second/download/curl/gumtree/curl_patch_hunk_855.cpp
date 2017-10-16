 "USING PASSWORDS\n"
 "\n"
 " FTP\n"
 "\n"
 "   To ftp files using name+passwd, include them in the URL like:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl ftp://name:passwd@machine.domain:port/full/path/to/file\n"
 "\n"
 "   or specify them with the -u flag like\n"
 "\n"
-, stdout);
- fputs(
 "        curl -u name:passwd ftp://machine.domain:port/full/path/to/file\n"
 "\n"
 " FTPS\n"
 "\n"
 "   It is just like for FTP, but you may also want to specify and use\n"
 "   SSL-specific options for certificates etc.\n"
 "\n"
 "   Note that using FTPS:// as prefix is the \"implicit\" way as described in the\n"
 "   standards while the recommended \"explicit\" way is done by using FTP:// and\n"
 "   the --ftp-ssl option.\n"
 "\n"
+, stdout);
+ fputs(
 " SFTP / SCP\n"
 "\n"
-"   This is similar to FTP, but you can specify a private key to use instead of\n"
+"   This is similar to FTP, but you can use the --key option to specify a\n"
+"   private key to use instead of a password. Note that the private key may\n"
+"   itself be protected by a password that is unrelated to the login password\n"
+"   of the remote system; this password is specified using the --pass option.\n"
+"   Typically, curl will automatically extract the public key from the private\n"
+"   key file, but in cases where curl does not have the proper library support,\n"
 , stdout);
  fputs(
-"   a password. Note that the private key may itself be protected by a password\n"
-"   that is unrelated to the login password of the remote system.  If you\n"
-"   provide a private key file you must also provide a public key file.\n"
+"   a matching public key file must be specified using the --pubkey option.\n"
 "\n"
 " HTTP\n"
 "\n"
 "   Curl also supports user and password in HTTP URLs, thus you can pick a file\n"
 "   like:\n"
 "\n"
 "        curl http://name:passwd@machine.domain/full/path/to/file\n"
 "\n"
 "   or specify user and password separately like in\n"
 "\n"
-, stdout);
- fputs(
 "        curl -u name:passwd http://machine.domain/full/path/to/file\n"
 "\n"
 "   HTTP offers many different methods of authentication and curl supports\n"
+, stdout);
+ fputs(
 "   several: Basic, Digest, NTLM and Negotiate (SPNEGO). Without telling which\n"
 "   method to use, curl defaults to Basic. You can also ask curl to pick the\n"
 "   most secure ones out of the ones that the server accepts for the given URL,\n"
 "   by using --anyauth.\n"
 "\n"
 "   NOTE! According to the URL specification, HTTP URLs can not contain a user\n"
-, stdout);
- fputs(
 "   and password, so that style will not work when using curl via a proxy, even\n"
 "   though curl allows it at other times. When using a proxy, you _must_ use\n"
+, stdout);
+ fputs(
 "   the -u style for user and password.\n"
 "\n"
 " HTTPS\n"
 "\n"
 "   Probably most commonly used with private certificates, as explained below.\n"
 "\n"
 "PROXY\n"
 "\n"
 " curl supports both HTTP and SOCKS proxy servers, with optional authentication.\n"
 " It does not have special support for FTP proxy servers since there are no\n"
-, stdout);
- fputs(
 " standards for those, but it can still be made to work with many of them. You\n"
 " can also use both HTTP and SOCKS proxies to transfer files to and from FTP\n"
 " servers.\n"
 "\n"
+, stdout);
+ fputs(
 " Get an ftp file using an HTTP proxy named my-proxy that uses port 888:\n"
 "\n"
 "        curl -x my-proxy:888 ftp://ftp.leachsite.com/README\n"
 "\n"
 " Get a file from an HTTP server that requires user and password, using the\n"
 " same proxy as above:\n"
 "\n"
 "        curl -u user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
-, stdout);
- fputs(
 " Some proxies require special authentication. Specify by using -U as above:\n"
 "\n"
 "        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
+, stdout);
+ fputs(
 " A comma-separated list of hosts and domains which do not use the proxy can\n"
 " be specified as:\n"
 "\n"
 "        curl --noproxy localhost,get.this -x my-proxy:888 http://www.get.this/\n"
 "\n"
 " If the proxy is specified with --proxy1.0 instead of --proxy or -x, then\n"
 " curl will use HTTP/1.0 instead of HTTP/1.1 for any CONNECT attempts.\n"
 "\n"
-, stdout);
- fputs(
 " curl also supports SOCKS4 and SOCKS5 proxies with --socks4 and --socks5.\n"
 "\n"
 " See also the environment variables Curl supports that offer further proxy\n"
 " control.\n"
 "\n"
+, stdout);
+ fputs(
 " Most FTP proxy servers are set up to appear as a normal FTP server from the\n"
 " client's perspective, with special commands to select the remote FTP server.\n"
 " curl supports the -u, -Q and --ftp-account options that can be used to\n"
 " set up transfers through many FTP proxies. For example, a file can be\n"
-, stdout);
- fputs(
 " uploaded to a remote FTP server using a Blue Coat FTP proxy with the\n"
 " options:\n"
 "\n"
 "   curl -u \"Remote-FTP-Username@remote.ftp.server Proxy-Username:Remote-Pass\" \\\n"
+, stdout);
+ fputs(
 "    --ftp-account Proxy-Password --upload-file local-file \\\n"
 "    ftp://my-ftp.proxy.server:21/remote/upload/path/\n"
 "\n"
 " See the manual for your FTP proxy to determine the form it expects to set up\n"
 " transfers, and curl's -v option to see exactly what curl is sending.\n"
 "\n"
 "RANGES\n"
 "\n"
 "  HTTP 1.1 introduced byte-ranges. Using this, a client can request\n"
-, stdout);
- fputs(
 "  to get only one or more subparts of a specified document. Curl supports\n"
 "  this with the -r flag.\n"
 "\n"
 "  Get the first 100 bytes of a document:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl -r 0-99 http://www.get.this/\n"
 "\n"
 "  Get the last 500 bytes of a document:\n"
 "\n"
 "        curl -r -500 http://www.get.this/\n"
 "\n"
