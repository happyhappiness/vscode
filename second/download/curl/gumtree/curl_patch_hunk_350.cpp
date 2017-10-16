 "   or specify them with the -u flag like\n"
 "\n"
 "        curl -u name:passwd ftp://machine.domain:port/full/path/to/file\n"
 "\n"
 " FTPS\n"
 "\n"
-, stdout);
- fputs(
 "   It is just like for FTP, but you may also want to specify and use\n"
 "   SSL-specific options for certificates etc.\n"
 "\n"
+, stdout);
+ fputs(
 "   Note that using FTPS:// as prefix is the \"implicit\" way as described in the\n"
 "   standards while the recommended \"explicit\" way is done by using FTP:// and\n"
 "   the --ftp-ssl option.\n"
 "\n"
 " SFTP / SCP\n"
 "\n"
 "   This is similar to FTP, but you can specify a private key to use instead of\n"
 "   a password. Note that the private key may itself be protected by a password\n"
-, stdout);
- fputs(
 "   that is unrelated to the login password of the remote system.  If you\n"
 "   provide a private key file you must also provide a public key file.\n"
+, stdout);
+ fputs(
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
 "        curl -u name:passwd http://machine.domain/full/path/to/file\n"
 "\n"
-, stdout);
- fputs(
 "   HTTP offers many different methods of authentication and curl supports\n"
 "   several: Basic, Digest, NTLM and Negotiate. Without telling which method to\n"
+, stdout);
+ fputs(
 "   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
 "   ones out of the ones that the server accepts for the given URL, by using\n"
 "   --anyauth.\n"
 "\n"
 "   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
 "   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
-, stdout);
- fputs(
 "   during such circumstances.\n"
 "\n"
 " HTTPS\n"
 "\n"
 "   Probably most commonly used with private certificates, as explained below.\n"
 "\n"
 "PROXY\n"
 "\n"
+, stdout);
+ fputs(
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
-, stdout);
- fputs(
 "        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
+, stdout);
+ fputs(
 " curl also supports SOCKS4 and SOCKS5 proxies with --socks4 and --socks5.\n"
 "\n"
 " See also the environment variables Curl support that offer further proxy\n"
 " control.\n"
 "\n"
 "RANGES\n"
