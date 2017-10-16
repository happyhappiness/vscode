 , stdout);
  fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -s, --silent\n"
 "              Silent  or  quiet  mode. Don't show progress meter or error mes-\n"
-"              sages.  Makes Curl mute.\n"
+"              sages.  Makes Curl mute. It will still output the data  you  ask\n"
+"              for, potentially even to the terminal/stdout unless you redirect\n"
+"              it.\n"
 "\n"
 "       -S, --show-error\n"
 "              When used with -s it makes curl show  an  error  message  if  it\n"
 "              fails.\n"
 "\n"
-"       --ssl  (FTP,  POP3,  IMAP, SMTP) Try to use SSL/TLS for the connection.\n"
 , stdout);
  fputs(
+"       --ssl  (FTP,  POP3,  IMAP, SMTP) Try to use SSL/TLS for the connection.\n"
 "              Reverts to a non-secure connection if the server doesn't support\n"
 "              SSL/TLS.   See also --ftp-ssl-control and --ssl-reqd for differ-\n"
 "              ent levels of encryption required. (Added in 7.20.0)\n"
 "\n"
 "              This option was formerly known as --ftp-ssl (Added  in  7.11.0).\n"
 "              That  option  name  can  still  be used but will be removed in a\n"
 "              future version.\n"
 "\n"
-"       --ssl-reqd\n"
 , stdout);
  fputs(
+"       --ssl-reqd\n"
 "              (FTP, POP3, IMAP, SMTP)  Require  SSL/TLS  for  the  connection.\n"
 "              Terminates the connection if the server doesn't support SSL/TLS.\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "              This option was  formerly  known  as  --ftp-ssl-reqd  (added  in\n"
 "              7.15.5).  That option name can still be used but will be removed\n"
 "              in a future version.\n"
 "\n"
 "       --ssl-allow-beast\n"
-"              (SSL) This option tells curl to not work around a security  flaw\n"
 , stdout);
  fputs(
+"              (SSL) This option tells curl to not work around a security  flaw\n"
 "              in the SSL3 and TLS1.0 protocols known as BEAST.  If this option\n"
 "              isn't used, the SSL layer may use work-arounds  known  to  cause\n"
 "              interoperability  problems  with some older SSL implementations.\n"
 "              WARNING: this option loosens the SSL security, and by using this\n"
 "              flag you ask for exactly that.  (Added in 7.25.0)\n"
 "\n"
 "       --socks4 <host[:port]>\n"
-"              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
 , stdout);
  fputs(
+"              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
 "              fied, it is assumed at port 1080. (Added in 7.15.2)\n"
 "\n"
 "              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks4 proxy with -x, --proxy using a socks4:// protocol prefix.\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks4a <host[:port]>\n"
-, stdout);
- fputs(
 "              Use the specified SOCKS4a proxy. If the port number is not spec-\n"
 "              ified, it is assumed at port 1080. (Added in 7.18.0)\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
+, stdout);
+ fputs(
 "              socks4a  proxy with -x, --proxy using a socks4a:// protocol pre-\n"
 "              fix.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks5-hostname <host[:port]>\n"
 "              Use the specified SOCKS5 proxy (and let the  proxy  resolve  the\n"
 "              host  name).  If the port number is not specified, it is assumed\n"
 "              at port 1080. (Added in 7.18.0)\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
-, stdout);
- fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 hostname proxy with -x, --proxy using a socks5h:// proto-\n"
 "              col prefix.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This option was  previously  wrongly  documented  and  used  as\n"
+, stdout);
+ fputs(
 "              --socks without the number appended.)\n"
 "\n"
 "       --socks5 <host[:port]>\n"
-, stdout);
- fputs(
 "              Use  the  specified  SOCKS5  proxy  -  but resolve the host name\n"
 "              locally. If the port number is not specified, it is  assumed  at\n"
 "              port 1080.\n"
 "\n"
 "              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
-"              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
 , stdout);
  fputs(
+"              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This option was  previously  wrongly  documented  and  used  as\n"
 "              --socks without the number appended.)\n"
 "\n"
 "              This  option (as well as --socks4) does not work with IPV6, FTPS\n"
 "              or LDAP.\n"
 "\n"
 "       --socks5-gssapi-service <servicename>\n"
+, stdout);
+ fputs(
 "              The default service name for a socks server is rcmd/server-fqdn.\n"
 "              This option allows you to change it.\n"
 "\n"
-, stdout);
- fputs(
 "              Examples:   --socks5  proxy-name  --socks5-gssapi-service  sockd\n"
 "              would use sockd/proxy-name --socks5 proxy-name  --socks5-gssapi-\n"
 "              service  sockd/real-name  would  use  sockd/real-name  for cases\n"
 "              where the proxy-name does not match the principal name.   (Added\n"
 "              in 7.19.4).\n"
 "\n"
-"       --socks5-gssapi-nec\n"
-"              As  part  of the gssapi negotiation a protection mode is negoti-\n"
 , stdout);
  fputs(
+"       --socks5-gssapi-nec\n"
+"              As  part  of the gssapi negotiation a protection mode is negoti-\n"
 "              ated. RFC 1961 says in section 4.3/4.4 it should  be  protected,\n"
 "              but  the  NEC  reference  implementation  does  not.  The option\n"
 "              --socks5-gssapi-nec allows the unprotected exchange of the  pro-\n"
 "              tection mode negotiation. (Added in 7.19.4).\n"
 "\n"
 "       --stderr <file>\n"
+, stdout);
+ fputs(
 "              Redirect  all writes to stderr to the specified file instead. If\n"
 "              the file name is a plain '-', it is instead written to stdout.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -t, --telnet-option <OPT=val>\n"
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
 "              This transfers the specified local file to the  remote  URL.  If\n"
-, stdout);
- fputs(
 "              there is no file part in the specified URL, Curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory  to really prove to Curl that there is no file name or\n"
 "              curl will think that your last directory name is the remote file\n"
+, stdout);
+ fputs(
 "              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on an HTTP(S) server, the PUT command will\n"
 "              be used.\n"
 "\n"
-, stdout);
- fputs(
 "              Use  the file name \"-\" (a single dash) to use stdin instead of a\n"
 "              given file.  Alternately, the file name \".\"  (a  single  period)\n"
 "              may  be  specified  instead  of \"-\" to use stdin in non-blocking\n"
 "              mode to  allow  reading  server  output  while  stdin  is  being\n"
+, stdout);
+ fputs(
 "              uploaded.\n"
 "\n"
 "              You can specify one -T for each URL on the command line. Each -T\n"
-, stdout);
- fputs(
 "              + URL pair specifies what to upload and to where. curl also sup-\n"
 "              ports \"globbing\" of the -T argument, meaning that you can upload\n"
 "              multiple files to a single URL by using the  same  URL  globbing\n"
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
-, stdout);
- fputs(
 "              Turn  on the TCP_NODELAY option. See the curl_easy_setopt(3) man\n"
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
 "       --tftp-blksize <value>\n"
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
 "              size that curl will try to use when transferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
-"              If this option is used several times, the last one will be used.\n"
-"\n"
 , stdout);
  fputs(
+"              If this option is used several times, the last one will be used.\n"
+"\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "       --tlsauthtype <authtype>\n"
 "              Set TLS  authentication  type.  Currently,  the  only  supported\n"
 "              option  is  \"SRP\",  for  TLS-SRP  (RFC  5054).  If --tlsuser and\n"
 "              --tlspassword are specified but --tlsauthtype is not, then  this\n"
 "              option defaults to \"SRP\".  (Added in 7.21.4)\n"
 "\n"
 "       --tlsuser <user>\n"
-"              Set  username  for use with the TLS authentication method speci-\n"
 , stdout);
  fputs(
+"              Set  username  for use with the TLS authentication method speci-\n"
 "              fied with --tlsauthtype. Requires  that  --tlspassword  also  be\n"
 "              set.  (Added in 7.21.4)\n"
 "\n"
 "       --tlspassword <password>\n"
 "              Set  password  for use with the TLS authentication method speci-\n"
 "              fied with --tlsauthtype. Requires that --tlsuser  also  be  set.\n"
 "              (Added in 7.21.4)\n"
 "\n"
 "       --tr-encoding\n"
-"              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 , stdout);
  fputs(
+"              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 "              of the algorithms curl supports, and uncompress the  data  while\n"
 "              receiving it.\n"
 "\n"
 "              (Added in 7.21.6)\n"
 "\n"
 "       --trace <file>\n"
 "              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides previous uses of -v, --verbose or --trace-\n"
 "              ascii.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
-"              This is very similar to --trace, but leaves out the hex part and\n"
-"              only  shows  the ASCII part of the dump. It makes smaller output\n"
 , stdout);
  fputs(
+"              This is very similar to --trace, but leaves out the hex part and\n"
+"              only  shows  the ASCII part of the dump. It makes smaller output\n"
 "              that might be easier to read for untrained humans.\n"
 "\n"
 "              This option overrides previous uses of -v, --verbose or --trace.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
+, stdout);
+ fputs(
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "       -u, --user <user:password>\n"
 "              Specify the user name and password to use for server authentica-\n"
-, stdout);
- fputs(
 "              tion. Overrides -n, --netrc and --netrc-optional.\n"
 "\n"
 "              If you just give the user name (without entering a  colon)  curl\n"
 "              will prompt for a password.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
+, stdout);
+ fputs(
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-u :\".\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -U, --proxy-user <user:password>\n"
 "              Specify the user name and password to use for proxy  authentica-\n"
 "              tion.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
+, stdout);
+ fputs(
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-U :\".\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --url <URL>\n"
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  may  be used any number of times. To control where\n"
 "              this URL is written, use the -o, --output or the  -O,  --remote-\n"
 "              name options.\n"
 "       -v, --verbose\n"
-, stdout);
- fputs(
 "              Makes  the  fetching  more  verbose/talkative. Mostly useful for\n"
 "              debugging. A line starting with '>' means \"header data\" sent  by\n"
 "              curl, '<' means \"header data\" received by curl that is hidden in\n"
+, stdout);
+ fputs(
 "              normal cases, and a line starting with '*' means additional info\n"
 "              provided by curl.\n"
 "\n"
 "              Note  that  if  you  only  want  HTTP headers in the output, -i,\n"
 "              --include might be the option you're looking for.\n"
 "\n"
-, stdout);
- fputs(
 "              If you think this option still doesn't give you enough  details,\n"
 "              consider using --trace or --trace-ascii instead.\n"
 "\n"
 "              This option overrides previous uses of --trace-ascii or --trace.\n"
 "\n"
+, stdout);
+ fputs(
 "              Use -s, --silent to make curl quiet.\n"
 "\n"
 "       -w, --write-out <format>\n"
 "              Defines what to display on stdout after a completed and success-\n"
 "              ful operation. The format is a string  that  may  contain  plain\n"
-, stdout);
- fputs(
 "              text mixed with any number of variables. The string can be spec-\n"
 "              ified as \"string\", to get read from a particular file you  spec-\n"
 "              ify  it  \"@filename\"  and  to  tell curl to read the format from\n"
+, stdout);
+ fputs(
 "              stdin you write \"@-\".\n"
 "\n"
 "              The variables present in the output format will  be  substituted\n"
 "              by  the  value or text that curl thinks fit, as described below.\n"
-, stdout);
- fputs(
 "              All variables are specified as %{variable_name} and to output  a\n"
 "              normal  % you just write them as %%. You can output a newline by\n"
 "              using \\n, a carriage return with \\r and a tab space with \\t.\n"
 "\n"
+, stdout);
+ fputs(
 "              NOTE: The %-symbol is a special symbol in the win32-environment,\n"
 "              where  all  occurrences  of  %  must  be doubled when using this\n"
 "              option.\n"
 "\n"
 "              The variables available are:\n"
 "\n"
-, stdout);
- fputs(
 "              content_type   The Content-Type of the  requested  document,  if\n"
 "                             there was any.\n"
 "\n"
 "              filename_effective\n"
 "                             The  ultimate  filename  that curl writes out to.\n"
+, stdout);
+ fputs(
 "                             This is only meaningful if curl is told to  write\n"
 "                             to  a  file  with  the  --remote-name or --output\n"
 "                             option. It's most useful in combination with  the\n"
-, stdout);
- fputs(
 "                             --remote-header-name option. (Added in 7.25.1)\n"
 "\n"
 "              ftp_entry_path The initial path curl ended up in when logging on\n"
 "                             to the remote FTP server. (Added in 7.15.4)\n"
 "\n"
+, stdout);
+ fputs(
 "              http_code      The numerical response code that was found in the\n"
 "                             last  retrieved  HTTP(S)  or  FTP(s) transfer. In\n"
 "                             7.18.2 the alias response_code was added to  show\n"
-, stdout);
- fputs(
 "                             the same info.\n"
 "\n"
 "              http_connect   The  numerical  code  that  was found in the last\n"
 "                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 "                             request. (Added in 7.12.4)\n"
 "\n"
+, stdout);
+ fputs(
 "              local_ip       The  IP  address  of  the  local  end of the most\n"
 "                             recently done connection - can be either IPv4  or\n"
 "                             IPv6 (Added in 7.29.0)\n"
 "\n"
-, stdout);
- fputs(
 "              local_port     The  local  port number of the most recently done\n"
 "                             connection (Added in 7.29.0)\n"
 "\n"
 "              num_connects   Number of new connects made in the recent  trans-\n"
 "                             fer. (Added in 7.12.3)\n"
 "\n"
+, stdout);
+ fputs(
 "              num_redirects  Number  of  redirects  that  were followed in the\n"
 "                             request. (Added in 7.12.3)\n"
 "\n"
 "              redirect_url   When an HTTP request was made without -L to  fol-\n"
-, stdout);
- fputs(
 "                             low redirects, this variable will show the actual\n"
 "                             URL a redirect  would  take  you  to.  (Added  in\n"
 "                             7.18.2)\n"
 "\n"
 "              remote_ip      The  remote  IP address of the most recently done\n"
+, stdout);
+ fputs(
 "                             connection - can be either IPv4 or IPv6 (Added in\n"
 "                             7.29.0)\n"
 "\n"
 "              remote_port    The  remote port number of the most recently done\n"
-, stdout);
- fputs(
 "                             connection (Added in 7.29.0)\n"
 "\n"
 "              size_download  The total amount of bytes that were downloaded.\n"
 "\n"
 "              size_header    The total amount of bytes of the downloaded head-\n"
 "                             ers.\n"
 "\n"
+, stdout);
+ fputs(
 "              size_request   The  total  amount of bytes that were sent in the\n"
 "                             HTTP request.\n"
 "\n"
 "              size_upload    The total amount of bytes that were uploaded.\n"
 "\n"
-, stdout);
- fputs(
 "              speed_download The average download speed that curl measured for\n"
 "                             the complete download. Bytes per second.\n"
 "\n"
 "              speed_upload   The  average  upload speed that curl measured for\n"
 "                             the complete upload. Bytes per second.\n"
 "\n"
+, stdout);
+ fputs(
 "              ssl_verify_result\n"
 "                             The result of the SSL peer certificate  verifica-\n"
 "                             tion that was requested. 0 means the verification\n"
-, stdout);
- fputs(
 "                             was successful. (Added in 7.19.0)\n"
 "\n"
 "              time_appconnect\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  SSL/SSH/etc  connect/handshake to the\n"
+, stdout);
+ fputs(
 "                             remote host was completed. (Added in 7.19.0)\n"
 "\n"
 "              time_connect   The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  TCP  connect  to  the remote host (or\n"
-, stdout);
- fputs(
 "                             proxy) was completed.\n"
 "\n"
 "              time_namelookup\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
 "                             until the name resolving was completed.\n"
 "\n"
 "              time_pretransfer\n"
+, stdout);
+ fputs(
 "                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the file transfer was just about to  begin.\n"
 "                             This includes all pre-transfer commands and nego-\n"
-, stdout);
- fputs(
 "                             tiations that are specific to the particular pro-\n"
 "                             tocol(s) involved.\n"
 "\n"
 "              time_redirect  The time, in seconds, it took for all redirection\n"
+, stdout);
+ fputs(
 "                             steps include name lookup,  connect,  pretransfer\n"
 "                             and  transfer  before  the  final transaction was\n"
 "                             started. time_redirect shows the complete  execu-\n"
-, stdout);
- fputs(
 "                             tion  time  for  multiple redirections. (Added in\n"
 "                             7.12.3)\n"
 "\n"
 "              time_starttransfer\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
+, stdout);
+ fputs(
 "                             until  the first byte was just about to be trans-\n"
 "                             ferred. This includes time_pretransfer  and  also\n"
 "                             the  time  the  server  needed  to  calculate the\n"
-, stdout);
- fputs(
 "                             result.\n"
 "\n"
 "              time_total     The total time, in seconds, that the full  opera-\n"
 "                             tion lasted. The time will be displayed with mil-\n"
 "                             lisecond resolution.\n"
 "\n"
+, stdout);
+ fputs(
 "              url_effective  The URL that was fetched last. This is most mean-\n"
 "                             ingful  if  you've  told curl to follow location:\n"
 "                             headers.\n"
 "\n"
-, stdout);
- fputs(
 "       If this option is used several times, the last one will be used.\n"
 "\n"
 "       -x, --proxy <[protocol://][user:password@]proxyhost[:port]>\n"
 "              Use the specified HTTP proxy. If the port number is  not  speci-\n"
 "              fied, it is assumed at port 1080.\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  overrides  existing environment variables that set\n"
 "              the proxy to use. If there's an environment variable  setting  a\n"
 "              proxy, you can set proxy to \"\" to override it.\n"
 "\n"
-, stdout);
- fputs(
 "              All operations that are performed over an HTTP proxy will trans-\n"
 "              parently be converted to HTTP. It means  that  certain  protocol\n"
 "              specific operations might not be available. This is not the case\n"
+, stdout);
+ fputs(
 "              if you can tunnel through the proxy, as one with the -p, --prox-\n"
 "              ytunnel option.\n"
 "\n"
 "              User and password that might be provided in the proxy string are\n"
-, stdout);
- fputs(
 "              URL decoded by curl. This allows you to pass in special  charac-\n"
 "              ters such as @ by using %40 or pass in a colon with %3a.\n"
 "\n"
 "              The  proxy host can be specified the exact same way as the proxy\n"
 "              environment variables, including the protocol  prefix  (http://)\n"
+, stdout);
+ fputs(
 "              and the embedded user + password.\n"
 "\n"
 "              From  7.21.7,  the  proxy  string may be specified with a proto-\n"
-, stdout);
- fputs(
 "              col://  prefix  to  specify  alternative  proxy  protocols.  Use\n"
 "              socks4://,  socks4a://,  socks5://  or socks5h:// to request the\n"
 "              specific SOCKS  version  to  be  used.  No  protocol  specified,\n"
 "              http:// and all others will be treated as HTTP proxies.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X, --request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
-, stdout);
- fputs(
 "              ing with the HTTP server.  The specified request  will  be  used\n"
 "              instead  of  the  method otherwise used (which defaults to GET).\n"
 "              Read the HTTP 1.1 specification for  details  and  explanations.\n"
+, stdout);
+ fputs(
 "              Common  additional  HTTP  requests  include  PUT and DELETE, but\n"
 "              related technologies like WebDAV offers PROPFIND, COPY, MOVE and\n"
 "              more.\n"
 "\n"
 "              Normally  you  don't  need  this option. All sorts of GET, HEAD,\n"
-, stdout);
- fputs(
 "              POST and PUT requests are rather invoked by using dedicated com-\n"
 "              mand line options.\n"
 "\n"
 "              This  option  only  changes  the  actual  word  used in the HTTP\n"
+, stdout);
+ fputs(
 "              request, it does not alter the way curl behaves. So for  example\n"
 "              if  you  want  to make a proper HEAD request, using -X HEAD will\n"
 "              not suffice. You need to use the -I, --head option.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
-, stdout);
- fputs(
 "              doing file lists with FTP.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --xattr\n"
+, stdout);
+ fputs(
 "              When  saving  output  to a file, this option tells curl to store\n"
 "              certain file metadata in extened file attributes. Currently, the\n"
 "              URL is stored in the xdg.origin.url attribute and, for HTTP, the\n"
 "              content type is stored in the mime_type attribute. If  the  file\n"
-, stdout);
- fputs(
 "              system  does  not  support  extended  attributes,  a  warning is\n"
 "              issued.\n"
 "\n"
 "       -y, --speed-time <time>\n"
+, stdout);
+ fputs(
 "              If a download is slower than speed-limit bytes per second during\n"
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -Y.\n"
 "\n"
 "              This option controls transfers and thus  will  not  affect  slow\n"
-, stdout);
- fputs(
 "              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
 "              If a download is slower than this given speed (in bytes per sec-\n"
 "              ond)  for  speed-time seconds it gets aborted. speed-time is set\n"
 "              with -y and is 30 if not set.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z/--time-cond <date expression>|<file>\n"
+, stdout);
+ fputs(
 "              (HTTP/FTP) Request a file that has been modified later than  the\n"
 "              given  time  and date, or one that has been modified before that\n"
 "              time. The <date expression> can be all sorts of date strings  or\n"
 "              if it doesn't match any internal ones, it is taken as a filename\n"
-, stdout);
- fputs(
 "              and tries to get  the  modification  date  (mtime)  from  <file>\n"
 "              instead.  See  the curl_getdate(3) man pages for date expression\n"
 "              details.\n"
 "\n"
+, stdout);
+ fputs(
 "              Start the date expression with a dash (-) to make it request for\n"
 "              a  document that is older than the given date/time, default is a\n"
 "              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       -h, --help\n"
 "              Usage help.\n"
 "\n"
 "       -M, --manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -V, --version\n"
+, stdout);
+ fputs(
 "              Displays information about curl and the libcurl version it uses.\n"
 "              The first line includes the full version of  curl,  libcurl  and\n"
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
 "              The  second  line (starts with \"Protocols:\") shows all protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
+"              The third line (starts with \"Features:\") shows specific features\n"
 , stdout);
  fputs(
-"              The third line (starts with \"Features:\") shows specific features\n"
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
 "              krb4   Krb4 for FTP is supported.\n"
 "\n"
