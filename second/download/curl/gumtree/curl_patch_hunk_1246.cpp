 "              Examples:   --negotiate   --service-name   sockd    would    use\n"
 "              sockd/server-name.\n"
 "\n"
 "              Added in 7.43.0.\n"
 "       -S, --show-error\n"
 "              When used with -s, --silent, it makes curl show an error message\n"
-, stdout);
- fputs(
 "              if it fails.\n"
 "       -s, --silent\n"
+, stdout);
+ fputs(
 "              Silent or quiet mode. Don't show progress meter  or  error  mes-\n"
 "              sages.   Makes  Curl mute. It will still output the data you ask\n"
 "              for, potentially even to the terminal/stdout unless you redirect\n"
 "              it.\n"
 "\n"
 "              Use  -S,  --show-error  in  addition  to  this option to disable\n"
 "              progress meter but still show error messages.\n"
 "\n"
 "              See also -v, --verbose and --stderr.\n"
 "\n"
+"       --socks4 <host[:port]>\n"
 , stdout);
  fputs(
-"       --socks4 <host[:port]>\n"
 "              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
 "              fied, it is assumed at port 1080.\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks4 proxy with -x, --proxy using a socks4:// protocol prefix.\n"
+"              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
 , stdout);
  fputs(
-"              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
 "              the same time -x, --proxy is used with an HTTP/HTTPS  proxy.  In\n"
 "              such a case curl first connects to the SOCKS proxy and then con-\n"
 "              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              Added in 7.15.2.\n"
 "\n"
 "       --socks4a <host[:port]>\n"
-, stdout);
- fputs(
 "              Use the specified SOCKS4a proxy. If the port number is not spec-\n"
 "              ified, it is assumed at port 1080.\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks4a  proxy with -x, --proxy using a socks4a:// protocol pre-\n"
 "              fix.\n"
 "\n"
-, stdout);
- fputs(
 "              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
 "              the  same  time -x, --proxy is used with an HTTP/HTTPS proxy. In\n"
+, stdout);
+ fputs(
 "              such a case curl first connects to the SOCKS proxy and then con-\n"
 "              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              Added in 7.18.0.\n"
 "\n"
+"       --socks5-basic\n"
+"              Tells curl to use username/password authentication when connect-\n"
+"              ing to a SOCKS5 proxy.  The username/password authentication  is\n"
+, stdout);
+ fputs(
+"              enabled  by  default.   Use  --socks5-gssapi  to  force  GSS-API\n"
+"              authentication to SOCKS5 proxies.\n"
+"\n"
+"              Added in 7.55.0.\n"
+"\n"
 "       --socks5-gssapi-nec\n"
+"              As part of the GSS-API negotiation a protection mode is  negoti-\n"
+"              ated.  RFC  1961 says in section 4.3/4.4 it should be protected,\n"
+"              but the NEC  reference  implementation  does  not.   The  option\n"
 , stdout);
  fputs(
-"              As  part of the GSS-API negotiation a protection mode is negoti-\n"
-"              ated. RFC 1961 says in section 4.3/4.4 it should  be  protected,\n"
-"              but  the  NEC  reference  implementation  does  not.  The option\n"
-"              --socks5-gssapi-nec allows the unprotected exchange of the  pro-\n"
+"              --socks5-gssapi-nec  allows the unprotected exchange of the pro-\n"
 "              tection mode negotiation.\n"
 "\n"
 "              Added in 7.19.4.\n"
 "\n"
 "       --socks5-gssapi-service <name>\n"
-, stdout);
- fputs(
 "              The default service name for a socks server is rcmd/server-fqdn.\n"
 "              This option allows you to change it.\n"
 "\n"
-"              Examples:  --socks5  proxy-name  --socks5-gssapi-service   sockd\n"
-"              would  use sockd/proxy-name --socks5 proxy-name --socks5-gssapi-\n"
-"              service sockd/real-name  would  use  sockd/real-name  for  cases\n"
+"              Examples:   --socks5  proxy-name  --socks5-gssapi-service  sockd\n"
+"              would use sockd/proxy-name --socks5 proxy-name  --socks5-gssapi-\n"
+, stdout);
+ fputs(
+"              service  sockd/real-name  would  use  sockd/real-name  for cases\n"
 "              where the proxy-name does not match the principal name.\n"
 "\n"
 "              Added in 7.19.4.\n"
 "\n"
+"       --socks5-gssapi\n"
+"              Tells curl to use GSS-API authentication when  connecting  to  a\n"
+"              SOCKS5  proxy.  The GSS-API authentication is enabled by default\n"
+"              (if curl is compiled with GSS-API support).  Use  --socks5-basic\n"
 , stdout);
  fputs(
+"              to force username/password authentication to SOCKS5 proxies.\n"
+"\n"
+"              Added in 7.55.0.\n"
+"\n"
 "       --socks5-hostname <host[:port]>\n"
 "              Use  the  specified  SOCKS5 proxy (and let the proxy resolve the\n"
 "              host name). If the port number is not specified, it  is  assumed\n"
 "              at port 1080.\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
-"              Since 7.21.7, this option is superfluous since you can specify a\n"
 , stdout);
  fputs(
+"              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 hostname proxy with -x, --proxy using a socks5h:// proto-\n"
 "              col prefix.\n"
 "\n"
 "              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
 "              the  same  time -x, --proxy is used with an HTTP/HTTPS proxy. In\n"
 "              such a case curl first connects to the SOCKS proxy and then con-\n"
 "              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
 "\n"
-"              If this option is used several times, the last one will be used.\n"
-"\n"
 , stdout);
  fputs(
+"              If this option is used several times, the last one will be used.\n"
+"\n"
 "              Added in 7.18.0.\n"
 "\n"
 "       --socks5 <host[:port]>\n"
 "              Use  the  specified  SOCKS5  proxy  -  but resolve the host name\n"
 "              locally. If the port number is not specified, it is  assumed  at\n"
 "              port 1080.\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
-"              Since 7.21.7, this option is superfluous since you can specify a\n"
 , stdout);
  fputs(
+"              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
 "              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
 "              the same time -x, --proxy is used with an HTTP/HTTPS  proxy.  In\n"
 "              such a case curl first connects to the SOCKS proxy and then con-\n"
 "              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
 "\n"
-"              If this option is used several times, the last one will be used.\n"
 , stdout);
  fputs(
+"              If this option is used several times, the last one will be used.\n"
 "              This option (as well as --socks4) does not work with IPV6,  FTPS\n"
 "              or LDAP.\n"
 "\n"
 "              Added in 7.18.0.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
 "              If a download is slower than this given speed (in bytes per sec-\n"
 "              ond) for speed-time seconds it gets aborted. speed-time  is  set\n"
 "              with -y, --speed-time and is 30 if not set.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -y, --speed-time <seconds>\n"
-, stdout);
- fputs(
 "              If a download is slower than speed-limit bytes per second during\n"
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used,  the  default  speed-limit  will  be 1 unless set with -Y,\n"
 "              --speed-limit.\n"
 "\n"
 "              This option controls transfers and thus  will  not  affect  slow\n"
+, stdout);
+ fputs(
 "              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --ssl-allow-beast\n"
 "              This option tells curl to not work around a security flaw in the\n"
 "              SSL3  and TLS1.0 protocols known as BEAST.  If this option isn't\n"
 "              used, the SSL layer may use workarounds known to cause  interop-\n"
-"              erability problems with some older SSL implementations. WARNING:\n"
-"              this option loosens the SSL security, and by using this flag you\n"
 , stdout);
  fputs(
+"              erability problems with some older SSL implementations. WARNING:\n"
+"              this option loosens the SSL security, and by using this flag you\n"
 "              ask for exactly that.\n"
 "\n"
 "              Added in 7.25.0.\n"
 "\n"
 "       --ssl-no-revoke\n"
 "              (WinSSL)  This  option tells curl to disable certificate revoca-\n"
 "              tion checks.  WARNING: this option loosens the SSL security, and\n"
 "              by using this flag you ask for exactly that.\n"
 "\n"
 "              Added in 7.44.0.\n"
 "\n"
-"       --ssl-reqd\n"
-"              (FTP IMAP POP3 SMTP) Require SSL/TLS for the connection.  Termi-\n"
 , stdout);
  fputs(
+"       --ssl-reqd\n"
+"              (FTP IMAP POP3 SMTP) Require SSL/TLS for the connection.  Termi-\n"
 "              nates the connection if the server doesn't support SSL/TLS.\n"
 "\n"
 "              This option was formerly known as --ftp-ssl-reqd.\n"
 "\n"
 "              Added in 7.20.0.\n"
 "\n"
 "       --ssl  (FTP IMAP POP3 SMTP) Try to  use  SSL/TLS  for  the  connection.\n"
 "              Reverts to a non-secure connection if the server doesn't support\n"
+, stdout);
+ fputs(
 "              SSL/TLS.  See also --ftp-ssl-control and --ssl-reqd for  differ-\n"
 "              ent levels of encryption required.\n"
 "\n"
-, stdout);
- fputs(
 "              This  option  was formerly known as --ftp-ssl (Added in 7.11.0).\n"
 "              That option name can still be used but  will  be  removed  in  a\n"
 "              future version.\n"
 "\n"
 "              Added in 7.20.0.\n"
 "\n"
 "       -2, --sslv2\n"
 "              (SSL)  Forces  curl to use SSL version 2 when negotiating with a\n"
+, stdout);
+ fputs(
 "              remote SSL server. Sometimes curl is built  without  SSLv2  sup-\n"
 "              port. SSLv2 is widely considered insecure (see RFC 6176).\n"
 "\n"
-, stdout);
- fputs(
 "              See  also  --http1.1  and --http2. -2, --sslv2 requires that the\n"
 "              underlying libcurl was built to support TLS. This  option  over-\n"
 "              rides -3, --sslv3 and -1, --tlsv1 and --tlsv1.1 and --tlsv1.2.\n"
 "\n"
 "       -3, --sslv3\n"
 "              (SSL)  Forces  curl to use SSL version 3 when negotiating with a\n"
+, stdout);
+ fputs(
 "              remote SSL server. Sometimes curl is built  without  SSLv3  sup-\n"
 "              port. SSLv3 is widely considered insecure (see RFC 7568).\n"
 "\n"
-, stdout);
- fputs(
 "              See  also  --http1.1  and --http2. -3, --sslv3 requires that the\n"
 "              underlying libcurl was built to support TLS. This  option  over-\n"
 "              rides -2, --sslv2 and -1, --tlsv1 and --tlsv1.1 and --tlsv1.2.\n"
 "\n"
 "       --stderr\n"
 "              Redirect  all writes to stderr to the specified file instead. If\n"
+, stdout);
+ fputs(
 "              the file name is a plain '-', it is instead written to stdout.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "              See also -v, --verbose and -s, --silent.\n"
 "\n"
 "       --suppress-connect-headers\n"
 "              When -p, --proxytunnel is used and a  CONNECT  request  is  made\n"
 "              don't  output  proxy  CONNECT  response  headers. This option is\n"
 "              meant to be used with -D, --dump-header or -i,  --include  which\n"
-"              are  used  to  show  protocol  headers  in the output. It has no\n"
-"              effect on debug options such as -v, --verbose or --trace, or any\n"
 , stdout);
  fputs(
+"              are  used  to  show  protocol  headers  in the output. It has no\n"
+"              effect on debug options such as -v, --verbose or --trace, or any\n"
 "              statistics.\n"
 "\n"
 "              See also -D, --dump-header and -i, --include and -p, --proxytun-\n"
 "              nel.\n"
 "\n"
 "       --tcp-fastopen\n"
 "              Enable use of TCP Fast Open (RFC7413).\n"
 "\n"
 "              Added in 7.49.0.\n"
 "\n"
 "       --tcp-nodelay\n"
 "              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
+, stdout);
+ fputs(
 "              page for details about this option.\n"
 "\n"
 "              Since  7.50.2,  curl sets this option by default and you need to\n"
-, stdout);
- fputs(
 "              explicitly switch it off if you don't want it on.\n"
 "\n"
 "              Added in 7.11.2.\n"
 "\n"
 "       -t, --telnet-option <opt=val>\n"
 "              Pass options to the telnet protocol. Supported options are:\n"
 "\n"
 "              TTYPE=<term> Sets the terminal type.\n"
 "\n"
 "              XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
+, stdout);
+ fputs(
 "              NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
 "       --tftp-blksize <value>\n"
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
-, stdout);
- fputs(
 "              size that curl will try to use when transferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              Added in 7.20.0.\n"
 "\n"
 "       --tftp-no-options\n"
+, stdout);
+ fputs(
 "              (TFTP) Tells curl not to send TFTP options requests.\n"
 "\n"
 "              This option improves interop with some legacy  servers  that  do\n"
-, stdout);
- fputs(
 "              not  acknowledge  or  properly implement TFTP options. When this\n"
 "              option is used --tftp-blksize is ignored.\n"
 "\n"
 "              Added in 7.48.0.\n"
 "\n"
 "       -z, --time-cond <time>\n"
 "              (HTTP FTP) Request a file that has been modified later than  the\n"
-"              given  time  and date, or one that has been modified before that\n"
-"              time. The <date expression> can be all sorts of date strings  or\n"
 , stdout);
  fputs(
+"              given  time  and date, or one that has been modified before that\n"
+"              time. The <date expression> can be all sorts of date strings  or\n"
 "              if it doesn't match any internal ones, it is taken as a filename\n"
 "              and tries to get  the  modification  date  (mtime)  from  <file>\n"
 "              instead.  See  the curl_getdate(3) man pages for date expression\n"
 "              details.\n"
 "\n"
 "              Start the date expression with a dash (-) to make it request for\n"
+, stdout);
+ fputs(
 "              a  document that is older than the given date/time, default is a\n"
 "              document that is newer than the specified date/time.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --tls-max <VERSION>\n"
 "              (SSL) VERSION defines maximum supported TLS version.  A  minimum\n"
 "              is defined by arguments tlsv1.0 or tlsv1.1 or tlsv1.2.\n"
 "\n"
 "              default\n"
 "                     Use up to recommended TLS version.\n"
 "\n"
+, stdout);
+ fputs(
 "              1.0    Use up to TLSv1.0.\n"
 "              1.1    Use up to TLSv1.1.\n"
 "              1.2    Use up to TLSv1.2.\n"
 "              1.3    Use up to TLSv1.3.\n"
 "\n"
-, stdout);
- fputs(
 "       See also --tlsv1.0 and --tlsv1.1 and --tlsv1.2. --tls-max requires that\n"
 "       the underlying libcurl was built to support TLS. Added in 7.54.0.\n"
 "\n"
 "       --tlsauthtype <type>\n"
 "              Set TLS  authentication  type.  Currently,  the  only  supported\n"
 "              option  is  \"SRP\",  for  TLS-SRP  (RFC  5054).  If --tlsuser and\n"
+, stdout);
+ fputs(
 "              --tlspassword are specified but --tlsauthtype is not, then  this\n"
 "              option defaults to \"SRP\".\n"
 "\n"
 "              Added in 7.21.4.\n"
 "\n"
-, stdout);
- fputs(
 "       --tlspassword\n"
 "              Set  password  for use with the TLS authentication method speci-\n"
 "              fied with --tlsauthtype. Requires that --tlsuser also be set.\n"
 "\n"
 "              Added in 7.21.4.\n"
 "       --tlsuser <name>\n"
 "              Set username for use with the TLS authentication  method  speci-\n"
+, stdout);
+ fputs(
 "              fied  with  --tlsauthtype.  Requires  that --tlspassword also is\n"
 "              set.\n"
 "\n"
 "              Added in 7.21.4.\n"
 "\n"
 "       --tlsv1.0\n"
-, stdout);
- fputs(
 "              (TLS) Forces curl to use TLS version 1.0 when  connecting  to  a\n"
 "              remote TLS server.\n"
 "\n"
 "              Added in 7.34.0.\n"
 "\n"
 "       --tlsv1.1\n"
 "              (TLS)  Forces  curl  to use TLS version 1.1 when connecting to a\n"
 "              remote TLS server.\n"
 "\n"
 "              Added in 7.34.0.\n"
 "\n"
 "       --tlsv1.2\n"
+, stdout);
+ fputs(
 "              (TLS) Forces curl to use TLS version 1.2 when  connecting  to  a\n"
 "              remote TLS server.\n"
 "\n"
 "              Added in 7.34.0.\n"
 "\n"
 "       --tlsv1.3\n"
-, stdout);
- fputs(
 "              (TLS)  Forces  curl  to use TLS version 1.3 when connecting to a\n"
 "              remote TLS server.\n"
 "\n"
 "              Note that TLS 1.3 is only supported by a subset of TLS backends.\n"
 "              At the time of writing this, those are BoringSSL and NSS only.\n"
 "\n"
 "              Added in 7.52.0.\n"
 "\n"
 "       -1, --tlsv1\n"
+, stdout);
+ fputs(
 "              (SSL)  Tells curl to use TLS version 1.x when negotiating with a\n"
 "              remote TLS server. That means TLS version 1.0, 1.1 or 1.2.\n"
 "\n"
-, stdout);
- fputs(
 "              See also --http1.1 and --http2. -1, --tlsv1  requires  that  the\n"
 "              underlying  libcurl  was built to support TLS. This option over-\n"
 "              rides --tlsv1.1 and --tlsv1.2 and --tlsv1.3.\n"
 "\n"
 "       --tr-encoding\n"
 "              (HTTP) Request a compressed Transfer-Encoding response using one\n"
+, stdout);
+ fputs(
 "              of  the  algorithms curl supports, and uncompress the data while\n"
 "              receiving it.\n"
 "\n"
 "              Added in 7.21.6.\n"
 "\n"
 "       --trace-ascii <file>\n"
-, stdout);
- fputs(
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
 "              This is very similar to --trace, but leaves out the hex part and\n"
+, stdout);
+ fputs(
 "              only  shows  the ASCII part of the dump. It makes smaller output\n"
 "              that might be easier to read for untrained humans.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              This option overrides --trace and -v, --verbose.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
 "              displays.\n"
 "\n"
 "              Added in 7.14.0.\n"
 "\n"
 "       --trace <file>\n"
-"              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
-"              including descriptive information, to the given output file. Use\n"
 , stdout);
  fputs(
+"              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
+"              including descriptive information, to the given output file. Use\n"
 "              \"-\"  as  filename  to have the output sent to stdout. Use \"%\" as\n"
 "              filename to have the output sent to stderr.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              This option overrides -v, --verbose and --trace-ascii.\n"
 "\n"
 "       --unix-socket <path>\n"
+, stdout);
+ fputs(
 "              (HTTP) Connect through this Unix domain socket, instead of using\n"
 "              the network.\n"
 "\n"
 "              Added in 7.40.0.\n"
 "\n"
 "       -T, --upload-file <file>\n"
-, stdout);
- fputs(
 "              This  transfers  the  specified local file to the remote URL. If\n"
 "              there is no file part in the specified URL, curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory to really prove to Curl that there is no file name  or\n"
-"              curl will think that your last directory name is the remote file\n"
-"              name to use. That will most likely cause the upload operation to\n"
 , stdout);
  fputs(
+"              curl will think that your last directory name is the remote file\n"
+"              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on an HTTP(S) server, the PUT command will\n"
 "              be used.\n"
 "\n"
 "              Use the file name \"-\" (a single dash) to use stdin instead of  a\n"
 "              given  file.   Alternately,  the file name \".\" (a single period)\n"
 "              may be specified instead of \"-\" to  use  stdin  in  non-blocking\n"
+, stdout);
+ fputs(
 "              mode  to  allow  reading  server  output  while  stdin  is being\n"
 "              uploaded.\n"
 "\n"
-, stdout);
- fputs(
 "              You can specify one -T, --upload-file for each URL on  the  com-\n"
 "              mand  line.  Each -T, --upload-file + URL pair specifies what to\n"
 "              upload and to where. curl also supports \"globbing\"  of  the  -T,\n"
 "              --upload-file  argument,  meaning  that  you can upload multiple\n"
 "              files to a single URL by using the same URL globbing style  sup-\n"
-"              ported in the URL, like this:\n"
-"\n"
 , stdout);
  fputs(
+"              ported in the URL, like this:\n"
+"\n"
 "               curl --upload-file \"{file1,file2}\" http://www.example.com\n"
 "\n"
 "              or even\n"
 "\n"
 "               curl -T \"img[1-1000].png\" ftp://ftp.example.com/upload/\n"
 "\n"
 "              When  uploading  to an SMTP server: the uploaded data is assumed\n"
 "              to be RFC 5322 formatted. It has to feature the necessary set of\n"
 "              headers  and  mail  body formatted correctly by the user as curl\n"
+, stdout);
+ fputs(
 "              will not transcode nor encode it further in any way.\n"
 "\n"
 "       --url <url>\n"
-, stdout);
- fputs(
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
 "              If  the given URL is missing a scheme name (such as \"http://\" or\n"
 "              \"ftp://\" etc) then curl will make a guess based on the host.  If\n"
 "              the  outermost  sub-domain  name  matches DICT, FTP, IMAP, LDAP,\n"
-"              POP3 or SMTP then that protocol will  be  used,  otherwise  HTTP\n"
 , stdout);
  fputs(
+"              POP3 or SMTP then that protocol will  be  used,  otherwise  HTTP\n"
 "              will be used. Since 7.45.0 guessing can be disabled by setting a\n"
 "              default protocol, see --proto-default for details.\n"
 "\n"
 "              This option may be used any number of times.  To  control  where\n"
 "              this  URL  is written, use the -o, --output or the -O, --remote-\n"
 "              name options.\n"
 "\n"
 "       -B, --use-ascii\n"
-"              (FTP LDAP) Enable ASCII transfer. For  FTP,  this  can  also  be\n"
 , stdout);
  fputs(
+"              (FTP LDAP) Enable ASCII transfer. For  FTP,  this  can  also  be\n"
 "              enforced  by  using  a URL that ends with \";type=A\". This option\n"
 "              causes data sent to stdout to be in text mode for win32 systems.\n"
 "\n"
 "       -A, --user-agent <name>\n"
 "              (HTTP) Specify the User-Agent string to send to the HTTP server.\n"
 "              To  encode blanks in the string, surround the string with single\n"
+, stdout);
+ fputs(
 "              quote marks. This can also be set with the -H,  --header  option\n"
 "              of course.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -u, --user <user:password>\n"
 "              Specify the user name and password to use for server authentica-\n"
 "              tion. Overrides -n, --netrc and --netrc-optional.\n"
 "\n"
 "              If you simply specify the user name,  curl  will  prompt  for  a\n"
 "              password.\n"
 "\n"
-"              The  user  name  and  passwords are split up on the first colon,\n"
 , stdout);
  fputs(
+"              The  user  name  and  passwords are split up on the first colon,\n"
 "              which makes it impossible to use a colon in the user  name  with\n"
 "              this option. The password can, still.\n"
 "\n"
 "              When  using  Kerberos  V5 with a Windows based server you should\n"
 "              include the Windows domain name in the user name, in  order  for\n"
 "              the  server  to  successfully  obtain  a Kerberos Ticket. If you\n"
-"              don't then the initial authentication handshake may fail.\n"
-"\n"
 , stdout);
  fputs(
+"              don't then the initial authentication handshake may fail.\n"
+"\n"
 "              When using NTLM, the user name can be specified  simply  as  the\n"
 "              user  name,  without the domain, if there is a single domain and\n"
 "              forest in your setup for example.\n"
 "\n"
 "              To specify the domain name use either Down-Level Logon  Name  or\n"
 "              UPN (User Principal Name) formats. For example, EXAMPLE\\user and\n"
 "              user@example.com respectively.\n"
 "\n"
-"              If you use a Windows SSPI-enabled curl binary and  perform  Ker-\n"
 , stdout);
  fputs(
+"              If you use a Windows SSPI-enabled curl binary and  perform  Ker-\n"
 "              beros  V5, Negotiate, NTLM or Digest authentication then you can\n"
 "              tell curl to select the user name and password from  your  envi-\n"
 "              ronment by specifying a single colon with this option: \"-u :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -v, --verbose\n"
 "              Makes  curl  verbose  during the operation. Useful for debugging\n"
-"              and seeing what's going on \"under the  hood\".  A  line  starting\n"
 , stdout);
  fputs(
+"              and seeing what's going on \"under the  hood\".  A  line  starting\n"
 "              with  '>'  means  \"header  data\" sent by curl, '<' means \"header\n"
 "              data\" received by curl that is hidden in  normal  cases,  and  a\n"
 "              line starting with '*' means additional info provided by curl.\n"
 "\n"
 "              If you only want HTTP headers in the output, -i, --include might\n"
 "              be the option you're looking for.\n"
 "\n"
-"              If you think this option still doesn't give you enough  details,\n"
 , stdout);
  fputs(
+"              If you think this option still doesn't give you enough  details,\n"
 "              consider using --trace or --trace-ascii instead.\n"
 "\n"
 "              Use -s, --silent to make curl really quiet.\n"
 "\n"
 "              See  also  -i,  --include.  This  option  overrides  --trace and\n"
 "              --trace-ascii.\n"
 "\n"
 "       -V, --version\n"
 "              Displays information about curl and the libcurl version it uses.\n"
 "              The first line includes the full version of  curl,  libcurl  and\n"
-"              other 3rd party libraries linked with the executable.\n"
-"\n"
 , stdout);
  fputs(
+"              other 3rd party libraries linked with the executable.\n"
+"\n"
 "              The  second  line (starts with \"Protocols:\") shows all protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
 "              The third line (starts with \"Features:\") shows specific features\n"
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
 "              krb4   Krb4 for FTP is supported.\n"
 "\n"
-"              SSL    SSL  versions of various protocols are supported, such as\n"
 , stdout);
  fputs(
+"              SSL    SSL  versions of various protocols are supported, such as\n"
 "                     HTTPS, FTPS, POP3S and so on.\n"
 "\n"
 "              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
 "                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
-"              AsynchDNS\n"
 , stdout);
  fputs(
+"              AsynchDNS\n"
 "                     This  curl  uses asynchronous name resolves. Asynchronous\n"
 "                     name resolves can be done using either the c-ares or  the\n"
 "                     threaded resolver backends.\n"
 "\n"
 "              SPNEGO SPNEGO authentication is supported.\n"
 "\n"
 "              Largefile\n"
 "                     This curl supports transfers of large files, files larger\n"
 "                     than 2GB.\n"
 "\n"
 "              IDN    This curl supports IDN - international domain names.\n"
 "\n"
-"              GSS-API\n"
 , stdout);
  fputs(
+"              GSS-API\n"
 "                     GSS-API is supported.\n"
 "\n"
 "              SSPI   SSPI is supported.\n"
 "\n"
 "              TLS-SRP\n"
 "                     SRP (Secure Remote Password) authentication is  supported\n"
