 "       --proto-redir <protocols>\n"
 "              Tells  curl to use the listed protocols on redirect. See --proto\n"
 "              for how protocols are represented.\n"
 "\n"
 "              Example:\n"
 "\n"
-, stdout);
- fputs(
 "              --proto-redir -all,http,https\n"
 "                     Allow only HTTP and HTTPS on redirect.\n"
 "\n"
+, stdout);
+ fputs(
 "       By default curl will allow all protocols  on  redirect  except  several\n"
 "       disabled  for security reasons: Since 7.19.4 FILE and SCP are disabled,\n"
 "       and since 7.40.0 SMB and SMBS are also disabled. Specifying all or +all\n"
 "       enables  all  protocols on redirect, including those disabled for secu-\n"
 "       rity.\n"
 "\n"
 "       (Added in 7.20.2)\n"
 "\n"
 "       --proxy-anyauth\n"
+"              Tells curl to pick a suitable authentication method when  commu-\n"
 , stdout);
  fputs(
-"              Tells curl to pick a suitable authentication method when  commu-\n"
 "              nicating  with  the  given  proxy.  This  might  cause  an extra\n"
 "              request/response round-trip. (Added in 7.13.2)\n"
 "\n"
 "       --proxy-basic\n"
 "              Tells curl to use HTTP Basic authentication  when  communicating\n"
 "              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
 "              remote host. Basic is the  default  authentication  method  curl\n"
-, stdout);
- fputs(
 "              uses with proxies.\n"
 "\n"
 "       --proxy-digest\n"
+, stdout);
+ fputs(
 "              Tells  curl to use HTTP Digest authentication when communicating\n"
 "              with the given proxy. Use --digest for enabling HTTP Digest with\n"
 "              a remote host.\n"
 "\n"
 "       --proxy-negotiate\n"
 "              Tells  curl  to  use HTTP Negotiate (SPNEGO) authentication when\n"
 "              communicating with the given proxy. Use --negotiate for enabling\n"
-, stdout);
- fputs(
 "              HTTP Negotiate (SPNEGO) with a remote host. (Added in 7.17.1)\n"
 "\n"
 "       --proxy-ntlm\n"
+, stdout);
+ fputs(
 "              Tells  curl  to  use HTTP NTLM authentication when communicating\n"
 "              with the given proxy. Use --ntlm for enabling NTLM with a remote\n"
 "              host.\n"
 "\n"
 "       --proxy-service-name <servicename>\n"
 "              This  option  allows  you  to  change the service name for proxy\n"
 "              negotiation.\n"
 "\n"
-, stdout);
- fputs(
 "              Examples:  --proxy-negotiate   proxy-name   --proxy-service-name\n"
 "              sockd would use sockd/proxy-name.  (Added in 7.43.0).\n"
 "\n"
+, stdout);
+ fputs(
 "       --proxy1.0 <proxyhost[:port]>\n"
 "              Use  the  specified  HTTP  1.0  proxy. If the port number is not\n"
 "              specified, it is assumed at port 1080.\n"
 "\n"
 "              The only difference between this and the HTTP proxy option  (-x,\n"
 "              --proxy), is that attempts to use CONNECT through the proxy will\n"
-, stdout);
- fputs(
 "              specify an HTTP 1.0 protocol instead of the default HTTP 1.1.\n"
 "\n"
 "       --pubkey <key>\n"
+, stdout);
+ fputs(
 "              (SSH) Public key file name. Allows you to  provide  your  public\n"
 "              key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (As of 7.39.0, curl attempts to automatically extract the public\n"
 "              key from the private key file, so passing this option is  gener-\n"
+"              ally not required. Note that this public key extraction requires\n"
 , stdout);
  fputs(
-"              ally not required. Note that this public key extraction requires\n"
 "              libcurl to be linked against a copy of libssh2 1.2.8  or  higher\n"
 "              that is itself linked against OpenSSL.)\n"
 "\n"
 "       -q     If  used  as the first parameter on the command line, the curlrc\n"
 "              config file will not be read and used. See the -K, --config  for\n"
 "              details on the default config file search path.\n"
 "\n"
 "       -Q, --quote <command>\n"
+"              (FTP/SFTP)  Send  an arbitrary command to the remote FTP or SFTP\n"
 , stdout);
  fputs(
-"              (FTP/SFTP)  Send  an arbitrary command to the remote FTP or SFTP\n"
 "              server. Quote commands are sent BEFORE the transfer takes  place\n"
 "              (just  after  the  initial PWD command in an FTP transfer, to be\n"
 "              exact). To make commands take place after a successful transfer,\n"
 "              prefix  them  with  a  dash '-'.  To make commands be sent after\n"
 "              curl has changed the working directory, just before the transfer\n"
+"              command(s),  prefix  the  command  with a '+' (this is only sup-\n"
 , stdout);
  fputs(
-"              command(s),  prefix  the  command  with a '+' (this is only sup-\n"
 "              ported for FTP). You may specify any number of commands. If  the\n"
 "              server returns failure for one of the commands, the entire oper-\n"
 "              ation will be aborted. You must send syntactically  correct  FTP\n"
 "              commands  as  RFC 959 defines to FTP servers, or one of the com-\n"
 "              mands listed below to SFTP servers.  This  option  can  be  used\n"
+"              multiple  times. When speaking to an FTP server, prefix the com-\n"
 , stdout);
  fputs(
-"              multiple  times. When speaking to an FTP server, prefix the com-\n"
 "              mand with an asterisk (*) to make curl continue even if the com-\n"
 "              mand fails as by default curl will stop at first failure.\n"
 "\n"
 "              SFTP  is a binary protocol. Unlike for FTP, curl interprets SFTP\n"
 "              quote commands itself before sending them to the  server.   File\n"
 "              names may be quoted shell-style to embed spaces or special char-\n"
-, stdout);
- fputs(
 "              acters.  Following is the list of all supported SFTP quote  com-\n"
 "              mands:\n"
 "\n"
+, stdout);
+ fputs(
 "              chgrp group file\n"
 "                     The  chgrp command sets the group ID of the file named by\n"
 "                     the file operand to the group ID specified by  the  group\n"
 "                     operand. The group operand is a decimal integer group ID.\n"
 "\n"
 "              chmod mode file\n"
 "                     The  chmod  command  modifies  the  file mode bits of the\n"
-, stdout);
- fputs(
 "                     specified file. The mode operand is an octal integer mode\n"
 "                     number.\n"
 "\n"
+, stdout);
+ fputs(
 "              chown user file\n"
 "                     The chown command sets the owner of the file named by the\n"
 "                     file operand to the user ID specified by the  user  oper-\n"
 "                     and. The user operand is a decimal integer user ID.\n"
 "\n"
 "              ln source_file target_file\n"
 "                     The ln and symlink commands create a symbolic link at the\n"
-, stdout);
- fputs(
 "                     target_file location pointing to  the  source_file  loca-\n"
 "                     tion.\n"
 "\n"
+, stdout);
+ fputs(
 "              mkdir directory_name\n"
 "                     The  mkdir  command  creates  the  directory named by the\n"
 "                     directory_name operand.\n"
 "\n"
 "              pwd    The pwd command returns the absolute pathname of the cur-\n"
 "                     rent working directory.\n"
 "\n"
 "              rename source target\n"
-, stdout);
- fputs(
 "                     The rename command renames the file or directory named by\n"
 "                     the source operand to the destination path named  by  the\n"
+, stdout);
+ fputs(
 "                     target operand.\n"
 "\n"
 "              rm file\n"
 "                     The rm command removes the file specified by the file op-\n"
 "                     erand.\n"
 "\n"
 "              rmdir directory\n"
 "                     The rmdir command removes the directory  entry  specified\n"
-, stdout);
- fputs(
 "                     by the directory operand, provided it is empty.\n"
 "\n"
 "              symlink source_file target_file\n"
 "                     See ln.\n"
 "\n"
 "       -r, --range <range>\n"
+, stdout);
+ fputs(
 "              (HTTP/FTP/SFTP/FILE)  Retrieve a byte range (i.e a partial docu-\n"
 "              ment) from a HTTP/1.1, FTP or  SFTP  server  or  a  local  FILE.\n"
 "              Ranges can be specified in a number of ways.\n"
 "\n"
 "              0-499     specifies the first 500 bytes\n"
 "\n"
-, stdout);
- fputs(
 "              500-999   specifies the second 500 bytes\n"
 "\n"
 "              -500      specifies the last 500 bytes\n"
 "\n"
 "              9500-     specifies the bytes from offset 9500 and forward\n"
 "\n"
+, stdout);
+ fputs(
 "              0-0,-1    specifies the first and last byte only(*)(HTTP)\n"
 "\n"
 "              100-199,500-599\n"
 "                        specifies two separate 100-byte ranges(*) (HTTP)\n"
 "\n"
 "              (*)  = NOTE that this will cause the server to reply with a mul-\n"
 "              tipart response!\n"
 "\n"
-, stdout);
- fputs(
 "              Only digit characters (0-9) are valid in the 'start' and  'stop'\n"
 "              fields  of the 'start-stop' range syntax. If a non-digit charac-\n"
+, stdout);
+ fputs(
 "              ter is given in the range, the server's response will be unspec-\n"
 "              ified, depending on the server's configuration.\n"
 "\n"
 "              You  should also be aware that many HTTP/1.1 servers do not have\n"
 "              this feature enabled, so that when you attempt to get  a  range,\n"
-, stdout);
- fputs(
 "              you'll instead get the whole document.\n"
 "\n"
 "              FTP  and  SFTP  range  downloads only support the simple 'start-\n"
+, stdout);
+ fputs(
 "              stop' syntax (optionally with one of the numbers  omitted).  FTP\n"
 "              use depends on the extended FTP command SIZE.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -R, --remote-time\n"
 "              When  used,  this will make curl attempt to figure out the time-\n"
-, stdout);
- fputs(
 "              stamp of the remote file, and if  that  is  available  make  the\n"
 "              local file get that same timestamp.\n"
 "\n"
 "       --random-file <file>\n"
+, stdout);
+ fputs(
 "              (SSL) Specify the path name to file containing what will be con-\n"
 "              sidered as random data. The data is  used  to  seed  the  random\n"
 "              engine for SSL connections.  See also the --egd-file option.\n"
 "\n"
 "       --raw  (HTTP) When used, it disables all internal HTTP decoding of con-\n"
-, stdout);
- fputs(
 "              tent or transfer encodings and  instead  makes  them  passed  on\n"
 "              unaltered, raw. (Added in 7.16.2)\n"
 "\n"
 "       --remote-name-all\n"
+, stdout);
+ fputs(
 "              This  option changes the default action for all given URLs to be\n"
 "              dealt with as if -O, --remote-name were used for each one. So if\n"
 "              you want to disable that for a specific URL after --remote-name-\n"
 "              all has been used, you must  use  \"-o  -\"  or  --no-remote-name.\n"
-, stdout);
- fputs(
 "              (Added in 7.19.0)\n"
 "\n"
 "       --resolve <host:port:address>\n"
 "              Provide  a  custom  address  for  a specific host and port pair.\n"
+, stdout);
+ fputs(
 "              Using this, you can make the curl requests(s)  use  a  specified\n"
 "              address  and  prevent the otherwise normally resolved address to\n"
 "              be used. Consider it a sort of /etc/hosts  alternative  provided\n"
 "              on  the  command line. The port number should be the number used\n"
-, stdout);
- fputs(
 "              for the specific protocol the host will be used  for.  It  means\n"
 "              you  need several entries if you want to provide address for the\n"
+, stdout);
+ fputs(
 "              same host but different ports.\n"
 "\n"
 "              This option can be used many times to add  many  host  names  to\n"
 "              resolve.\n"
 "\n"
 "              (Added in 7.21.3)\n"
 "\n"
 "       --retry <num>\n"
 "              If  a  transient  error is returned when curl tries to perform a\n"
-, stdout);
- fputs(
 "              transfer, it will retry this number of times before  giving  up.\n"
 "              Setting  the  number to 0 makes curl do no retries (which is the\n"
+, stdout);
+ fputs(
 "              default). Transient error means either: a timeout,  an  FTP  4xx\n"
 "              response code or an HTTP 5xx response code.\n"
 "\n"
 "              When  curl  is about to retry a transfer, it will first wait one\n"
 "              second and then for all forthcoming retries it will  double  the\n"
-, stdout);
- fputs(
 "              waiting  time until it reaches 10 minutes which then will be the\n"
 "              delay between the rest of the retries.  By  using  --retry-delay\n"
+, stdout);
+ fputs(
 "              you   disable  this  exponential  backoff  algorithm.  See  also\n"
 "              --retry-max-time to limit the total time  allowed  for  retries.\n"
 "              (Added in 7.12.3)\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --retry-delay <seconds>\n"
-, stdout);
- fputs(
 "              Make  curl  sleep  this  amount of time before each retry when a\n"
 "              transfer has failed with  a  transient  error  (it  changes  the\n"
+, stdout);
+ fputs(
 "              default  backoff time algorithm between retries). This option is\n"
 "              only interesting if --retry is also used. Setting this delay  to\n"
 "              zero  will  make  curl  use the default backoff time.  (Added in\n"
 "              7.12.3)\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       --retry-max-time <seconds>\n"
 "              The retry timer is reset  before  the  first  transfer  attempt.\n"
+, stdout);
+ fputs(
 "              Retries will be done as usual (see --retry) as long as the timer\n"
 "              hasn't reached this given limit. Notice that if the timer hasn't\n"
 "              reached  the  limit, the request will be made and while perform-\n"
 "              ing, it may take longer than this given time period. To limit  a\n"
-, stdout);
- fputs(
 "              single  request's  maximum  time,  use -m, --max-time.  Set this\n"
 "              option to zero to not timeout retries. (Added in 7.12.3)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -s, --silent\n"
 "              Silent or quiet mode. Don't show progress meter  or  error  mes-\n"
 "              sages.   Makes  Curl mute. It will still output the data you ask\n"
 "              for, potentially even to the terminal/stdout unless you redirect\n"
-, stdout);
- fputs(
 "              it.\n"
 "\n"
 "       --sasl-ir\n"
 "              Enable  initial  response  in  SASL  authentication.   (Added in\n"
 "              7.31.0)\n"
 "\n"
+, stdout);
+ fputs(
 "       --service-name <servicename>\n"
 "              This option allows you to change the service name for SPNEGO.\n"
 "\n"
 "              Examples:   --negotiate   --service-name   sockd    would    use\n"
 "              sockd/server-name.  (Added in 7.43.0).\n"
 "\n"
 "       -S, --show-error\n"
 "              When  used  with  -s  it  makes curl show an error message if it\n"
-, stdout);
- fputs(
 "              fails.\n"
 "\n"
 "       --ssl  (FTP, POP3, IMAP, SMTP) Try to use SSL/TLS for  the  connection.\n"
+, stdout);
+ fputs(
 "              Reverts to a non-secure connection if the server doesn't support\n"
 "              SSL/TLS.  See also --ftp-ssl-control and --ssl-reqd for  differ-\n"
 "              ent levels of encryption required. (Added in 7.20.0)\n"
 "\n"
 "              This  option  was formerly known as --ftp-ssl (Added in 7.11.0).\n"
 "              That option name can still be used but  will  be  removed  in  a\n"
-, stdout);
- fputs(
 "              future version.\n"
 "\n"
 "       --ssl-reqd\n"
+, stdout);
+ fputs(
 "              (FTP,  POP3,  IMAP,  SMTP)  Require  SSL/TLS for the connection.\n"
 "              Terminates the connection if the server doesn't support SSL/TLS.\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "              This  option  was  formerly  known  as  --ftp-ssl-reqd (added in\n"
 "              7.15.5). That option name can still be used but will be  removed\n"
 "              in a future version.\n"
 "\n"
 "       --ssl-allow-beast\n"
+"              (SSL)  This option tells curl to not work around a security flaw\n"
 , stdout);
  fputs(
-"              (SSL)  This option tells curl to not work around a security flaw\n"
 "              in the SSL3 and TLS1.0 protocols known as BEAST.  If this option\n"
 "              isn't  used,  the  SSL  layer may use workarounds known to cause\n"
 "              interoperability problems with some older  SSL  implementations.\n"
 "              WARNING: this option loosens the SSL security, and by using this\n"
 "              flag you ask for exactly that.  (Added in 7.25.0)\n"
 "\n"
 "       --ssl-no-revoke\n"
+"              (WinSSL) This option tells curl to disable  certificate  revoca-\n"
 , stdout);
  fputs(
-"              (WinSSL) This option tells curl to disable  certificate  revoca-\n"
 "              tion checks.  WARNING: this option loosens the SSL security, and\n"
 "              by using this flag you ask for exactly that.  (Added in 7.44.0)\n"
 "\n"
 "       --socks4 <host[:port]>\n"
 "              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
 "              fied, it is assumed at port 1080. (Added in 7.15.2)\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
-, stdout);
- fputs(
 "              are mutually exclusive.\n"
 "\n"
+, stdout);
+ fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks4 proxy with -x, --proxy using a socks4:// protocol prefix.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks4a <host[:port]>\n"
 "              Use the specified SOCKS4a proxy. If the port number is not spec-\n"
 "              ified, it is assumed at port 1080. (Added in 7.18.0)\n"
 "\n"
+"              This option overrides any previous use of -x, --proxy,  as  they\n"
 , stdout);
  fputs(
-"              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks4a proxy with -x, --proxy using a socks4a:// protocol  pre-\n"
 "              fix.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks5-hostname <host[:port]>\n"
 "              Use  the  specified  SOCKS5 proxy (and let the proxy resolve the\n"
+"              host name). If the port number is not specified, it  is  assumed\n"
 , stdout);
  fputs(
-"              host name). If the port number is not specified, it  is  assumed\n"
 "              at port 1080. (Added in 7.18.0)\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 hostname proxy with -x, --proxy using a socks5h:// proto-\n"
 "              col prefix.\n"
 "\n"
+"              If this option is used several times, the last one will be used.\n"
 , stdout);
  fputs(
-"              If this option is used several times, the last one will be used.\n"
 "              (This  option  was  previously  wrongly  documented  and used as\n"
 "              --socks without the number appended.)\n"
 "\n"
 "       --socks5 <host[:port]>\n"
 "              Use the specified SOCKS5 proxy  -  but  resolve  the  host  name\n"
 "              locally.  If  the port number is not specified, it is assumed at\n"
 "              port 1080.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
+, stdout);
+ fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This  option  was  previously  wrongly  documented  and used as\n"
 "              --socks without the number appended.)\n"
 "\n"
-, stdout);
- fputs(
 "              This option (as well as --socks4) does not work with IPV6,  FTPS\n"
 "              or LDAP.\n"
 "\n"
+, stdout);
+ fputs(
 "       --socks5-gssapi-service <servicename>\n"
 "              The default service name for a socks server is rcmd/server-fqdn.\n"
 "              This option allows you to change it.\n"
 "\n"
 "              Examples:  --socks5  proxy-name  --socks5-gssapi-service   sockd\n"
 "              would  use sockd/proxy-name --socks5 proxy-name --socks5-gssapi-\n"
-, stdout);
- fputs(
 "              service sockd/real-name  would  use  sockd/real-name  for  cases\n"
 "              where  the proxy-name does not match the principal name.  (Added\n"
+, stdout);
+ fputs(
 "              in 7.19.4).\n"
 "\n"
 "       --socks5-gssapi-nec\n"
 "              As part of the GSS-API negotiation a protection mode is  negoti-\n"
 "              ated.  RFC  1961 says in section 4.3/4.4 it should be protected,\n"
 "              but the NEC  reference  implementation  does  not.   The  option\n"
-, stdout);
- fputs(
 "              --socks5-gssapi-nec  allows the unprotected exchange of the pro-\n"
 "              tection mode negotiation. (Added in 7.19.4).\n"
 "\n"
 "       --stderr <file>\n"
+, stdout);
+ fputs(
 "              Redirect all writes to stderr to the specified file instead.  If\n"
 "              the file name is a plain '-', it is instead written to stdout.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -t, --telnet-option <OPT=val>\n"
-, stdout);
- fputs(
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
 "       -T, --upload-file <file>\n"
 "              This  transfers  the  specified local file to the remote URL. If\n"
 "              there is no file part in the specified URL, Curl will append the\n"
-, stdout);
- fputs(
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory to really prove to Curl that there is no file name  or\n"
 "              curl will think that your last directory name is the remote file\n"
+, stdout);
+ fputs(
 "              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on an HTTP(S) server, the PUT command will\n"
 "              be used.\n"
 "\n"
 "              Use the file name \"-\" (a single dash) to use stdin instead of  a\n"
-, stdout);
- fputs(
 "              given  file.   Alternately,  the file name \".\" (a single period)\n"
 "              may be specified instead of \"-\" to  use  stdin  in  non-blocking\n"
 "              mode  to  allow  reading  server  output  while  stdin  is being\n"
+, stdout);
+ fputs(
 "              uploaded.\n"
 "\n"
 "              You can specify one -T for each URL on the command line. Each -T\n"
 "              + URL pair specifies what to upload and to where. curl also sup-\n"
-, stdout);
- fputs(
 "              ports \"globbing\" of the -T argument, meaning that you can upload\n"
 "              multiple  files  to  a single URL by using the same URL globbing\n"
 "              style supported in the URL, like this:\n"
 "\n"
 "              curl -T \"{file1,file2}\" http://www.uploadtothissite.com\n"
 "\n"
 "              or even\n"
 "\n"
+, stdout);
+ fputs(
 "              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
 "\n"
 "       --tcp-nodelay\n"
 "              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
-, stdout);
- fputs(
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
 "       --tftp-blksize <value>\n"
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
 "              size that curl will try to use when transferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "       --tlsauthtype <authtype>\n"
-, stdout);
- fputs(
 "              Set  TLS  authentication  type.  Currently,  the  only supported\n"
 "              option is \"SRP\",  for  TLS-SRP  (RFC  5054).  If  --tlsuser  and\n"
 "              --tlspassword  are specified but --tlsauthtype is not, then this\n"
 "              option defaults to \"SRP\".  (Added in 7.21.4)\n"
 "\n"
 "       --tlspassword <password>\n"
-"              Set password for use with the TLS authentication  method  speci-\n"
-"              fied  with  --tlsauthtype.  Requires that --tlsuser also be set.\n"
 , stdout);
  fputs(
+"              Set password for use with the TLS authentication  method  speci-\n"
+"              fied  with  --tlsauthtype.  Requires that --tlsuser also be set.\n"
 "              (Added in 7.21.4)\n"
 "\n"
 "       --tlsuser <user>\n"
 "              Set username for use with the TLS authentication  method  speci-\n"
 "              fied  with  --tlsauthtype.  Requires  that --tlspassword also be\n"
 "              set.  (Added in 7.21.4)\n"
 "\n"
 "       --tlsv1.0\n"
+, stdout);
+ fputs(
 "              (SSL) Forces curl to use TLS version 1.0 when negotiating with a\n"
 "              remote TLS server.  (Added in 7.34.0)\n"
 "\n"
 "       --tlsv1.1\n"
 "              (SSL) Forces curl to use TLS version 1.1 when negotiating with a\n"
-, stdout);
- fputs(
 "              remote TLS server.  (Added in 7.34.0)\n"
 "\n"
 "       --tlsv1.2\n"
 "              (SSL) Forces curl to use TLS version 1.2 when negotiating with a\n"
 "              remote TLS server.  (Added in 7.34.0)\n"
 "\n"
 "       --tr-encoding\n"
+, stdout);
+ fputs(
 "              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 "              of the algorithms curl supports, and uncompress the  data  while\n"
 "              receiving it.\n"
 "\n"
 "              (Added in 7.21.6)\n"
 "\n"
 "       --trace <file>\n"
-, stdout);
- fputs(
 "              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides previous uses of -v, --verbose or --trace-\n"
 "              ascii.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
-, stdout);
- fputs(
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
+, stdout);
+ fputs(
 "              This is very similar to --trace, but leaves out the hex part and\n"
 "              only  shows  the ASCII part of the dump. It makes smaller output\n"
 "              that might be easier to read for untrained humans.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides previous uses of -v, --verbose or --trace.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
+, stdout);
+ fputs(
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "       --unix-socket <path>\n"
 "              (HTTP) Connect through this Unix domain socket, instead of using\n"
 "              the network. (Added in 7.40.0)\n"
 "\n"
 "       -u, --user <user:password>\n"
-, stdout);
- fputs(
 "              Specify the user name and password to use for server authentica-\n"
 "              tion. Overrides -n, --netrc and --netrc-optional.\n"
 "\n"
 "              If  you  simply  specify  the  user name, curl will prompt for a\n"
 "              password.\n"
 "\n"
+, stdout);
+ fputs(
 "              The user name and passwords are split up  on  the  first  colon,\n"
 "              which  makes  it impossible to use a colon in the user name with\n"
 "              this option. The password can, still.\n"
 "\n"
-, stdout);
- fputs(
 "              When using Kerberos V5 with a Windows based  server  you  should\n"
 "              include  the  Windows domain name in the user name, in order for\n"
 "              the server to successfully obtain  a  Kerberos  Ticket.  If  you\n"
+, stdout);
+ fputs(
 "              don't then the initial authentication handshake may fail.\n"
 "\n"
 "              When  using  NTLM,  the user name can be specified simply as the\n"
 "              user name, without the domain, if there is a single  domain  and\n"
-, stdout);
- fputs(
 "              forest in your setup for example.\n"
 "\n"
 "              To  specify  the domain name use either Down-Level Logon Name or\n"
 "              UPN (User Principal Name) formats. For example, EXAMPLE\\user and\n"
 "              user@example.com respectively.\n"
 "\n"
+, stdout);
+ fputs(
 "              If  you  use a Windows SSPI-enabled curl binary and perform Ker-\n"
 "              beros V5, Negotiate, NTLM or Digest authentication then you  can\n"
 "              tell  curl  to select the user name and password from your envi-\n"
-, stdout);
- fputs(
 "              ronment by specifying a single colon with this option: \"-u :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -U, --proxy-user <user:password>\n"
+, stdout);
+ fputs(
 "              Specify the user name and password to use for proxy  authentica-\n"
 "              tion.\n"
 "\n"
 "              If  you  use  a  Windows  SSPI-enabled curl binary and do either\n"
 "              Negotiate or NTLM authentication  then  you  can  tell  curl  to\n"
-, stdout);
- fputs(
 "              select the user name and password from your environment by spec-\n"
 "              ifying a single colon with this option: \"-U :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --url <URL>\n"
+, stdout);
+ fputs(
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
 "              If  the given URL is missing a scheme name (such as \"http://\" or\n"
-, stdout);
- fputs(
 "              \"ftp://\" etc) then curl will make a guess based on the host.  If\n"
 "              the  outermost  sub-domain  name  matches DICT, FTP, IMAP, LDAP,\n"
 "              POP3 or SMTP then that protocol will  be  used,  otherwise  HTTP\n"
+, stdout);
+ fputs(
 "              will be used. Since 7.45.0 guessing can be disabled by setting a\n"
 "              default protocol, see --proto-default for details.\n"
 "\n"
 "              This option may be used any number of times.  To  control  where\n"
-, stdout);
- fputs(
 "              this  URL  is written, use the -o, --output or the -O, --remote-\n"
 "              name options.\n"
 "       -v, --verbose\n"
 "              Be more  verbose/talkative  during  the  operation.  Useful  for\n"
+, stdout);
+ fputs(
 "              debugging  and  seeing  what's going on \"under the hood\". A line\n"
 "              starting with '>' means \"header data\" sent by  curl,  '<'  means\n"
 "              \"header  data\"  received by curl that is hidden in normal cases,\n"
-, stdout);
- fputs(
 "              and a line starting with '*' means additional info  provided  by\n"
 "              curl.\n"
 "\n"
 "              Note  that  if  you  only  want  HTTP headers in the output, -i,\n"
 "              --include might be the option you're looking for.\n"
 "\n"
+, stdout);
+ fputs(
 "              If you think this option still doesn't give you enough  details,\n"
 "              consider using --trace or --trace-ascii instead.\n"
 "\n"
 "              This option overrides previous uses of --trace-ascii or --trace.\n"
 "\n"
-, stdout);
- fputs(
 "              Use -s, --silent to make curl quiet.\n"
 "\n"
 "       -w, --write-out <format>\n"
 "              Make curl display information on stdout after a completed trans-\n"
 "              fer. The format is a string that may contain  plain  text  mixed\n"
+, stdout);
+ fputs(
 "              with  any  number of variables. The format can be specified as a\n"
 "              literal \"string\", or you can have curl read the  format  from  a\n"
 "              file  with  \"@filename\" and to tell curl to read the format from\n"
-, stdout);
- fputs(
 "              stdin you write \"@-\".\n"
 "\n"
 "              The variables present in the output format will  be  substituted\n"
 "              by  the  value or text that curl thinks fit, as described below.\n"
+, stdout);
+ fputs(
 "              All variables are specified as %{variable_name} and to output  a\n"
 "              normal  % you just write them as %%. You can output a newline by\n"
 "              using \\n, a carriage return with \\r and a tab space with \\t.\n"
 "\n"
-, stdout);
- fputs(
 "              NOTE: The %-symbol is a special symbol in the win32-environment,\n"
 "              where  all  occurrences  of  %  must  be doubled when using this\n"
 "              option.\n"
 "\n"
 "              The variables available are:\n"
 "\n"
+, stdout);
+ fputs(
 "              content_type   The Content-Type of the  requested  document,  if\n"
 "                             there was any.\n"
 "\n"
 "              filename_effective\n"
 "                             The  ultimate  filename  that curl writes out to.\n"
-, stdout);
- fputs(
 "                             This is only meaningful if curl is told to  write\n"
 "                             to  a  file  with  the  --remote-name or --output\n"
 "                             option. It's most useful in combination with  the\n"
+, stdout);
+ fputs(
 "                             --remote-header-name option. (Added in 7.25.1)\n"
 "\n"
 "              ftp_entry_path The initial path curl ended up in when logging on\n"
 "                             to the remote FTP server. (Added in 7.15.4)\n"
 "\n"
-, stdout);
- fputs(
 "              http_code      The numerical response code that was found in the\n"
 "                             last  retrieved  HTTP(S)  or  FTP(s) transfer. In\n"
 "                             7.18.2 the alias response_code was added to  show\n"
+, stdout);
+ fputs(
 "                             the same info.\n"
 "\n"
 "              http_connect   The  numerical  code  that  was found in the last\n"
 "                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 "                             request. (Added in 7.12.4)\n"
 "\n"
-, stdout);
- fputs(
 "              local_ip       The  IP  address  of  the  local  end of the most\n"
 "                             recently done connection - can be either IPv4  or\n"
 "                             IPv6 (Added in 7.29.0)\n"
 "\n"
+, stdout);
+ fputs(
 "              local_port     The  local  port number of the most recently done\n"
 "                             connection (Added in 7.29.0)\n"
 "\n"
 "              num_connects   Number of new connects made in the recent  trans-\n"
 "                             fer. (Added in 7.12.3)\n"
 "\n"
-, stdout);
- fputs(
 "              num_redirects  Number  of  redirects  that  were followed in the\n"
 "                             request. (Added in 7.12.3)\n"
 "\n"
 "              redirect_url   When an HTTP request was made without -L to  fol-\n"
+, stdout);
+ fputs(
 "                             low redirects, this variable will show the actual\n"
 "                             URL a redirect  would  take  you  to.  (Added  in\n"
 "                             7.18.2)\n"
 "\n"
 "              remote_ip      The  remote  IP address of the most recently done\n"
-, stdout);
- fputs(
 "                             connection - can be either IPv4 or IPv6 (Added in\n"
 "                             7.29.0)\n"
 "\n"
 "              remote_port    The  remote port number of the most recently done\n"
+, stdout);
+ fputs(
 "                             connection (Added in 7.29.0)\n"
 "\n"
 "              size_download  The total amount of bytes that were downloaded.\n"
 "\n"
 "              size_header    The total amount of bytes of the downloaded head-\n"
 "                             ers.\n"
 "\n"
-, stdout);
- fputs(
 "              size_request   The  total  amount of bytes that were sent in the\n"
 "                             HTTP request.\n"
 "\n"
 "              size_upload    The total amount of bytes that were uploaded.\n"
 "\n"
+, stdout);
+ fputs(
 "              speed_download The average download speed that curl measured for\n"
 "                             the complete download. Bytes per second.\n"
 "\n"
 "              speed_upload   The  average  upload speed that curl measured for\n"
 "                             the complete upload. Bytes per second.\n"
 "\n"
-, stdout);
- fputs(
 "              ssl_verify_result\n"
 "                             The result of the SSL peer certificate  verifica-\n"
 "                             tion that was requested. 0 means the verification\n"
+, stdout);
+ fputs(
 "                             was successful. (Added in 7.19.0)\n"
 "\n"
 "              time_appconnect\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  SSL/SSH/etc  connect/handshake to the\n"
-, stdout);
- fputs(
 "                             remote host was completed. (Added in 7.19.0)\n"
 "\n"
 "              time_connect   The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  TCP  connect  to  the remote host (or\n"
+, stdout);
+ fputs(
 "                             proxy) was completed.\n"
 "\n"
 "              time_namelookup\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
 "                             until the name resolving was completed.\n"
 "\n"
 "              time_pretransfer\n"
-, stdout);
- fputs(
 "                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the file transfer was just about to  begin.\n"
 "                             This includes all pre-transfer commands and nego-\n"
+, stdout);
+ fputs(
 "                             tiations that are specific to the particular pro-\n"
 "                             tocol(s) involved.\n"
 "\n"
 "              time_redirect  The time, in seconds, it took for all redirection\n"
-, stdout);
- fputs(
 "                             steps include name lookup,  connect,  pretransfer\n"
 "                             and  transfer  before  the  final transaction was\n"
 "                             started. time_redirect shows the complete  execu-\n"
+, stdout);
+ fputs(
 "                             tion  time  for  multiple redirections. (Added in\n"
 "                             7.12.3)\n"
 "\n"
 "              time_starttransfer\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
-, stdout);
- fputs(
 "                             until  the first byte was just about to be trans-\n"
 "                             ferred. This includes time_pretransfer  and  also\n"
 "                             the  time  the  server  needed  to  calculate the\n"
+, stdout);
+ fputs(
 "                             result.\n"
 "\n"
 "              time_total     The total time, in seconds, that the full  opera-\n"
 "                             tion lasted. The time will be displayed with mil-\n"
 "                             lisecond resolution.\n"
 "\n"
-, stdout);
- fputs(
 "              url_effective  The URL that was fetched last. This is most mean-\n"
 "                             ingful  if  you've  told curl to follow location:\n"
 "                             headers.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -x, --proxy <[protocol://][user:password@]proxyhost[:port]>\n"
 "              Use the specified proxy.\n"
 "\n"
 "              The proxy string can be specified with a protocol://  prefix  to\n"
-, stdout);
- fputs(
 "              specify  alternative proxy protocols. Use socks4://, socks4a://,\n"
 "              socks5:// or socks5h:// to request the specific SOCKS version to\n"
+, stdout);
+ fputs(
 "              be  used.  No protocol specified, http:// and all others will be\n"
 "              treated as HTTP proxies. (The protocol support was added in curl\n"
 "              7.21.7)\n"
 "\n"
 "              If  the  port number is not specified in the proxy string, it is\n"
 "              assumed to be 1080.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides existing environment  variables  that  set\n"
 "              the  proxy  to use. If there's an environment variable setting a\n"
+, stdout);
+ fputs(
 "              proxy, you can set proxy to \"\" to override it.\n"
 "\n"
 "              All operations that are performed over an HTTP proxy will trans-\n"
 "              parently  be  converted  to HTTP. It means that certain protocol\n"
 "              specific operations might not be available. This is not the case\n"
-, stdout);
- fputs(
 "              if you can tunnel through the proxy, as one with the -p, --prox-\n"
 "              ytunnel option.\n"
 "\n"
 "              User and password that might be provided in the proxy string are\n"
+, stdout);
+ fputs(
 "              URL  decoded by curl. This allows you to pass in special charac-\n"
 "              ters such as @ by using %40 or pass in a colon with %3a.\n"
 "\n"
 "              The proxy host can be specified the exact same way as the  proxy\n"
 "              environment  variables,  including the protocol prefix (http://)\n"
-, stdout);
- fputs(
 "              and the embedded user + password.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X, --request <command>\n"
+, stdout);
+ fputs(
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
 "              ing  with the HTTP server.  The specified request method will be\n"
 "              used instead of the method otherwise  used  (which  defaults  to\n"
 "              GET).  Read  the HTTP 1.1 specification for details and explana-\n"
-, stdout);
- fputs(
 "              tions. Common additional HTTP requests include PUT  and  DELETE,\n"
 "              but related technologies like WebDAV offers PROPFIND, COPY, MOVE\n"
 "              and more.\n"
 "\n"
+, stdout);
+ fputs(
 "              Normally you don't need this option. All  sorts  of  GET,  HEAD,\n"
 "              POST and PUT requests are rather invoked by using dedicated com-\n"
 "              mand line options.\n"
 "\n"
 "              This option only changes  the  actual  word  used  in  the  HTTP\n"
-, stdout);
- fputs(
 "              request,  it does not alter the way curl behaves. So for example\n"
 "              if you want to make a proper HEAD request, using  -X  HEAD  will\n"
 "              not suffice. You need to use the -I, --head option.\n"
 "\n"
+, stdout);
+ fputs(
 "              The method string you set with -X will be used for all requests,\n"
 "              which if you for example use -L, --location may cause unintended\n"
 "              side-effects  when  curl doesn't change request method according\n"
-, stdout);
- fputs(
 "              to the HTTP 30x response codes - and similar.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with FTP.\n"
 "\n"
 "              (POP3) Specifies a custom POP3 command to use instead of LIST or\n"
+, stdout);
+ fputs(
 "              RETR. (Added in 7.26.0)\n"
 "\n"
 "              (IMAP) Specifies a custom IMAP command to use instead  of  LIST.\n"
 "              (Added in 7.30.0)\n"
 "\n"
 "              (SMTP) Specifies a custom SMTP command to use instead of HELP or\n"
-, stdout);
- fputs(
 "              VRFY. (Added in 7.34.0)\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --xattr\n"
 "              When saving output to a file, this option tells  curl  to  store\n"
+, stdout);
+ fputs(
 "              certain  file  metadata  in extended file attributes. Currently,\n"
 "              the URL is stored in the xdg.origin.url attribute and, for HTTP,\n"
 "              the  content  type  is stored in the mime_type attribute. If the\n"
-, stdout);
- fputs(
 "              file system does not support extended attributes, a  warning  is\n"
 "              issued.\n"
 "\n"
 "       -y, --speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
+, stdout);
+ fputs(
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -Y.\n"
 "\n"
 "              This  option  controls  transfers  and thus will not affect slow\n"
-, stdout);
- fputs(
 "              connects etc. If this is a concern for you, try  the  --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
+, stdout);
+ fputs(
 "              If a download is slower than this given speed (in bytes per sec-\n"
 "              ond) for speed-time seconds it gets aborted. speed-time  is  set\n"
 "              with -y and is 30 if not set.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z, --time-cond <date expression>|<file>\n"
 "              (HTTP/FTP)  Request a file that has been modified later than the\n"
 "              given time and date, or one that has been modified  before  that\n"
-"              time.  The <date expression> can be all sorts of date strings or\n"
-"              if it doesn't match any internal ones, it is taken as a filename\n"
 , stdout);
  fputs(
+"              time.  The <date expression> can be all sorts of date strings or\n"
+"              if it doesn't match any internal ones, it is taken as a filename\n"
 "              and  tries  to  get  the  modification  date (mtime) from <file>\n"
 "              instead. See the curl_getdate(3) man pages for  date  expression\n"
 "              details.\n"
 "\n"
 "              Start the date expression with a dash (-) to make it request for\n"
 "              a document that is older than the given date/time, default is  a\n"
+, stdout);
+ fputs(
 "              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       -h, --help\n"
 "              Usage  help.  This lists all current command line options with a\n"
 "              short description.\n"
 "\n"
 "       -M, --manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -V, --version\n"
 "              Displays information about curl and the libcurl version it uses.\n"
+, stdout);
+ fputs(
 "              The first line includes the full version of  curl,  libcurl  and\n"
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
-, stdout);
- fputs(
 "              The  second  line (starts with \"Protocols:\") shows all protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
 "              The third line (starts with \"Features:\") shows specific features\n"
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
+, stdout);
+ fputs(
 "              krb4   Krb4 for FTP is supported.\n"
 "\n"
 "              SSL    SSL  versions of various protocols are supported, such as\n"
-, stdout);
- fputs(
 "                     HTTPS, FTPS, POP3S and so on.\n"
 "\n"
 "              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
+, stdout);
+ fputs(
 "                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
 "              AsynchDNS\n"
-, stdout);
- fputs(
 "                     This  curl  uses asynchronous name resolves. Asynchronous\n"
 "                     name resolves can be done using either the c-ares or  the\n"
 "                     threaded resolver backends.\n"
 "\n"
 "              SPNEGO SPNEGO authentication is supported.\n"
 "\n"
 "              Largefile\n"
+, stdout);
+ fputs(
 "                     This curl supports transfers of large files, files larger\n"
 "                     than 2GB.\n"
 "\n"
 "              IDN    This curl supports IDN - international domain names.\n"
 "\n"
 "              GSS-API\n"
-, stdout);
- fputs(
 "                     GSS-API is supported.\n"
 "\n"
 "              SSPI   SSPI is supported.\n"
 "\n"
 "              TLS-SRP\n"
 "                     SRP (Secure Remote Password) authentication is  supported\n"
 "                     for TLS.\n"
 "\n"
 "              HTTP2  HTTP/2 support has been built-in.\n"
 "\n"
+, stdout);
+ fputs(
 "              Metalink\n"
 "                     This  curl  supports  Metalink (both version 3 and 4 (RFC\n"
 "                     5854)), which describes mirrors and  hashes.   curl  will\n"
-, stdout);
- fputs(
 "                     use mirrors for failover if there are errors (such as the\n"
 "                     file or server not being available).\n"
 "\n"
 "FILES\n"
 "       ~/.curlrc\n"
 "              Default config file, see -K, --config for details.\n"
 "\n"
 "ENVIRONMENT\n"
 "       The environment variables can be specified in lower case or upper case.\n"
+, stdout);
+ fputs(
 "       The lower case version has precedence. http_proxy is an exception as it\n"
 "       is only available in lower case.\n"
 "\n"
-, stdout);
- fputs(
 "       Using an environment variable to set the proxy has the same  effect  as\n"
 "       using the --proxy option.\n"
 "\n"
 "       http_proxy [protocol://]<host>[:port]\n"
 "              Sets the proxy server to use for HTTP.\n"
 "       HTTPS_PROXY [protocol://]<host>[:port]\n"
 "              Sets the proxy server to use for HTTPS.\n"
 "\n"
 "       [url-protocol]_PROXY [protocol://]<host>[:port]\n"
-"              Sets  the proxy server to use for [url-protocol], where the pro-\n"
 , stdout);
  fputs(
+"              Sets  the proxy server to use for [url-protocol], where the pro-\n"
 "              tocol is a protocol that curl supports and  as  specified  in  a\n"
 "              URL. FTP, FTPS, POP3, IMAP, SMTP, LDAP etc.\n"
 "\n"
 "       ALL_PROXY [protocol://]<host>[:port]\n"
 "              Sets  the  proxy  server to use if no protocol-specific proxy is\n"
 "              set.\n"
 "\n"
 "       NO_PROXY <comma-separated list of hosts>\n"
 "              list of host names that shouldn't go through any proxy.  If  set\n"
+, stdout);
+ fputs(
 "              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "PROXY PROTOCOL PREFIXES\n"
-, stdout);
- fputs(
 "       Since  curl  version  7.21.7,  the proxy string may be specified with a\n"
 "       protocol:// prefix to specify alternative proxy protocols.\n"
 "\n"
 "       If no protocol is specified in  the  proxy  string  or  if  the  string\n"
 "       doesn't  match  a  supported  one, the proxy will be treated as an HTTP\n"
 "       proxy.\n"
 "\n"
 "       The supported proxy protocol prefixes are as follows:\n"
 "\n"
 "       socks4://\n"
+, stdout);
+ fputs(
 "              Makes it the equivalent of --socks4\n"
 "\n"
 "       socks4a://\n"
-, stdout);
- fputs(
 "              Makes it the equivalent of --socks4a\n"
 "\n"
 "       socks5://\n"
 "              Makes it the equivalent of --socks5\n"
 "\n"
 "       socks5h://\n"
