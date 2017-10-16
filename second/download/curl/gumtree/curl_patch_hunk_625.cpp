 "              but  the  NEC  reference  implementation  does  not.  The option\n"
 "              --socks5-gssapi-nec allows the unprotected exchange of the  pro-\n"
 "              tection mode negotiation. (Added in 7.19.4).\n"
 "\n"
 "       --stderr <file>\n"
 "              Redirect  all writes to stderr to the specified file instead. If\n"
-"              the file name is a plain '-', it is instead written  to  stdout.\n"
+"              the file name is a plain '-', it is instead written to stdout.\n"
+"\n"
 , stdout);
  fputs(
-"              This  option  has no point when you're using a shell with decent\n"
-"              redirecting capabilities.\n"
-"\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -t, --telnet-option <OPT=val>\n"
 "              Pass options to the telnet protocol. Supported options are:\n"
 "\n"
 "              TTYPE=<term> Sets the terminal type.\n"
 "\n"
 "              XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
 "              NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
-, stdout);
- fputs(
 "       -T, --upload-file <file>\n"
 "              This transfers the specified local file to the  remote  URL.  If\n"
+, stdout);
+ fputs(
 "              there is no file part in the specified URL, Curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory  to really prove to Curl that there is no file name or\n"
 "              curl will think that your last directory name is the remote file\n"
-, stdout);
- fputs(
 "              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on a HTTP(S) server, the PUT command  will\n"
 "              be used.\n"
 "\n"
+, stdout);
+ fputs(
 "              Use  the file name \"-\" (a single dash) to use stdin instead of a\n"
 "              given file.  Alternately, the file name \".\"  (a  single  period)\n"
 "              may  be  specified  instead  of \"-\" to use stdin in non-blocking\n"
 "              mode to  allow  reading  server  output  while  stdin  is  being\n"
-, stdout);
- fputs(
 "              uploaded.\n"
 "\n"
 "              You can specify one -T for each URL on the command line. Each -T\n"
+, stdout);
+ fputs(
 "              + URL pair specifies what to upload and to where. curl also sup-\n"
 "              ports \"globbing\" of the -T argument, meaning that you can upload\n"
 "              multiple files to a single URL by using the  same  URL  globbing\n"
 "              style supported in the URL, like this:\n"
 "\n"
 "              curl -T \"{file1,file2}\" http://www.uploadtothissite.com\n"
 "\n"
 "              or even\n"
 "\n"
-, stdout);
- fputs(
 "              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
 "\n"
 "       --tcp-nodelay\n"
+, stdout);
+ fputs(
 "              Turn  on the TCP_NODELAY option. See the curl_easy_setopt(3) man\n"
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
 "       --tftp-blksize <value>\n"
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
 "              size that curl will try to use when transferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "              (Added in 7.20.0)\n"
 "\n"
 "       --tlsauthtype <authtype>\n"
 "              Set TLS  authentication  type.  Currently,  the  only  supported\n"
 "              option  is  \"SRP\",  for  TLS-SRP  (RFC  5054).  If --tlsuser and\n"
 "              --tlspassword are specified but --tlsauthtype is not, then  this\n"
 "              option defaults to \"SRP\".  (Added in 7.21.4)\n"
 "\n"
 "       --tlsuser <user>\n"
+"              Set  username  for use with the TLS authentication method speci-\n"
 , stdout);
  fputs(
-"              Set  username  for use with the TLS authentication method speci-\n"
 "              fied with --tlsauthtype. Requires  that  --tlspassword  also  be\n"
 "              set.  (Added in 7.21.4)\n"
 "\n"
 "       --tlspassword <password>\n"
 "              Set  password  for use with the TLS authentication method speci-\n"
 "              fied with --tlsauthtype. Requires that --tlsuser  also  be  set.\n"
 "              (Added in 7.21.4)\n"
 "\n"
 "       --tr-encoding\n"
+"              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 , stdout);
  fputs(
-"              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 "              of the algorithms libcurl  supports,  and  uncompress  the  data\n"
 "              while receiving it.\n"
 "\n"
 "              (Added in 7.21.6)\n"
 "\n"
 "       --trace <file>\n"
 "              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides previous uses of -v, --verbose or --trace-\n"
 "              ascii.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
-, stdout);
- fputs(
 "              This is very similar to --trace, but leaves out the hex part and\n"
 "              only  shows  the ASCII part of the dump. It makes smaller output\n"
+, stdout);
+ fputs(
 "              that might be easier to read for untrained humans.\n"
 "\n"
 "              This option overrides previous uses of -v, --verbose or --trace.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
-, stdout);
- fputs(
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "       -u, --user <user:password>\n"
 "              Specify the user name and password to use for server authentica-\n"
+, stdout);
+ fputs(
 "              tion. Overrides -n, --netrc and --netrc-optional.\n"
 "\n"
 "              If you just give the user name (without entering a  colon)  curl\n"
 "              will prompt for a password.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
-, stdout);
- fputs(
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-u :\".\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -U, --proxy-user <user:password>\n"
 "              Specify the user name and password to use for proxy  authentica-\n"
 "              tion.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
-, stdout);
- fputs(
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-U :\".\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --url <URL>\n"
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
-, stdout);
- fputs(
 "              This  option  may  be used any number of times. To control where\n"
 "              this URL is written, use the -o, --output or the  -O,  --remote-\n"
 "              name options.\n"
 "       -v, --verbose\n"
+, stdout);
+ fputs(
 "              Makes  the  fetching  more  verbose/talkative. Mostly useful for\n"
 "              debugging. A line starting with '>' means \"header data\" sent  by\n"
 "              curl, '<' means \"header data\" received by curl that is hidden in\n"
-, stdout);
- fputs(
 "              normal cases, and a line starting with '*' means additional info\n"
 "              provided by curl.\n"
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
 "              Defines what to display on stdout after a completed and success-\n"
 "              ful operation. The format is a string  that  may  contain  plain\n"
+, stdout);
+ fputs(
 "              text mixed with any number of variables. The string can be spec-\n"
 "              ified as \"string\", to get read from a particular file you  spec-\n"
 "              ify  it  \"@filename\"  and  to  tell curl to read the format from\n"
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
 "              The variables available at this point are:\n"
 "\n"
+, stdout);
+ fputs(
 "              url_effective  The URL that was fetched last. This is most mean-\n"
 "                             ingful  if  you've  told curl to follow location:\n"
 "                             headers.\n"
 "\n"
-, stdout);
- fputs(
 "              http_code      The numerical response code that was found in the\n"
 "                             last  retrieved  HTTP(S)  or  FTP(s) transfer. In\n"
 "                             7.18.2 the alias response_code was added to  show\n"
 "                             the same info.\n"
 "\n"
+, stdout);
+ fputs(
 "              http_connect   The  numerical  code  that  was found in the last\n"
 "                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 "                             request. (Added in 7.12.4)\n"
 "\n"
-, stdout);
- fputs(
 "              time_total     The  total time, in seconds, that the full opera-\n"
 "                             tion lasted. The time will be displayed with mil-\n"
 "                             lisecond resolution.\n"
 "\n"
 "              time_namelookup\n"
+, stdout);
+ fputs(
 "                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the name resolving was completed.\n"
 "\n"
 "              time_connect   The time, in seconds,  it  took  from  the  start\n"
-, stdout);
- fputs(
 "                             until  the  TCP  connect  to  the remote host (or\n"
 "                             proxy) was completed.\n"
 "\n"
 "              time_appconnect\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
+, stdout);
+ fputs(
 "                             until  the  SSL/SSH/etc  connect/handshake to the\n"
 "                             remote host was completed. (Added in 7.19.0)\n"
 "\n"
 "              time_pretransfer\n"
-, stdout);
- fputs(
 "                             The time, in seconds,  it  took  from  the  start\n"
 "                             until  the file transfer was just about to begin.\n"
 "                             This includes all pre-transfer commands and nego-\n"
+, stdout);
+ fputs(
 "                             tiations that are specific to the particular pro-\n"
 "                             tocol(s) involved.\n"
 "\n"
 "              time_redirect  The time, in seconds, it took for all redirection\n"
-, stdout);
- fputs(
 "                             steps  include  name lookup, connect, pretransfer\n"
 "                             and transfer before  the  final  transaction  was\n"
 "                             started.  time_redirect shows the complete execu-\n"
+, stdout);
+ fputs(
 "                             tion time for multiple  redirections.  (Added  in\n"
 "                             7.12.3)\n"
 "\n"
 "              time_starttransfer\n"
 "                             The  time,  in  seconds,  it  took from the start\n"
-, stdout);
- fputs(
 "                             until the first byte was just about to be  trans-\n"
 "                             ferred.  This  includes time_pretransfer and also\n"
 "                             the time  the  server  needed  to  calculate  the\n"
+, stdout);
+ fputs(
 "                             result.\n"
 "\n"
 "              size_download  The total amount of bytes that were downloaded.\n"
 "\n"
 "              size_upload    The total amount of bytes that were uploaded.\n"
 "\n"
-, stdout);
- fputs(
 "              size_header    The total amount of bytes of the downloaded head-\n"
 "                             ers.\n"
 "\n"
 "              size_request   The total amount of bytes that were sent  in  the\n"
 "                             HTTP request.\n"
 "\n"
+, stdout);
+ fputs(
 "              speed_download The average download speed that curl measured for\n"
 "                             the complete download. Bytes per second.\n"
 "\n"
 "              speed_upload   The average upload speed that curl  measured  for\n"
-, stdout);
- fputs(
 "                             the complete upload. Bytes per second.\n"
 "\n"
 "              content_type   The  Content-Type  of  the requested document, if\n"
 "                             there was any.\n"
 "\n"
+, stdout);
+ fputs(
 "              num_connects   Number of new connects made in the recent  trans-\n"
 "                             fer. (Added in 7.12.3)\n"
 "\n"
 "              num_redirects  Number  of  redirects  that  were followed in the\n"
 "                             request. (Added in 7.12.3)\n"
 "\n"
-, stdout);
- fputs(
 "              redirect_url   When a HTTP request was made without -L to follow\n"
 "                             redirects, this variable will show the actual URL\n"
+, stdout);
+ fputs(
 "                             a redirect would take you to. (Added in 7.18.2)\n"
 "\n"
 "              ftp_entry_path The initial path libcurl ended up in when logging\n"
 "                             on to the remote FTP server. (Added in 7.15.4)\n"
 "\n"
 "              ssl_verify_result\n"
-, stdout);
- fputs(
 "                             The  result of the SSL peer certificate verifica-\n"
 "                             tion that was requested. 0 means the verification\n"
 "                             was successful. (Added in 7.19.0)\n"
 "\n"
+, stdout);
+ fputs(
 "       If this option is used several times, the last one will be used.\n"
 "\n"
 "       -x, --proxy <[protocol://][user@password]proxyhost[:port]>\n"
 "              Use  the  specified HTTP proxy. If the port number is not speci-\n"
 "              fied, it is assumed at port 1080.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides existing environment  variables  that  set\n"
 "              the  proxy  to use. If there's an environment variable setting a\n"
 "              proxy, you can set proxy to \"\" to override it.\n"
 "\n"
+, stdout);
+ fputs(
 "              All operations that are performed over a HTTP proxy will  trans-\n"
 "              parently  be  converted  to HTTP. It means that certain protocol\n"
 "              specific operations might not be available. This is not the case\n"
-, stdout);
- fputs(
 "              if you can tunnel through the proxy, as one with the -p, --prox-\n"
 "              ytunnel option.\n"
 "\n"
 "              The proxy host can be specified the exact same way as the  proxy\n"
+, stdout);
+ fputs(
 "              environment  variables,  including the protocol prefix (http://)\n"
 "              and the embedded user + password.\n"
 "\n"
 "              From 7.21.7, the proxy string may be  specified  with  a  proto-\n"
 "              col://  prefix  to  specify  alternative  proxy  protocols.  Use\n"
-, stdout);
- fputs(
 "              socks4://, socks4a://, socks5:// or socks5h://  to  request  the\n"
 "              specific  SOCKS  version  to  be  used.  No  protocol specified,\n"
+, stdout);
+ fputs(
 "              http:// and all others will be treated as HTTP proxies.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X, --request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
 "              ing  with  the  HTTP server.  The specified request will be used\n"
-, stdout);
- fputs(
 "              instead of the method otherwise used (which  defaults  to  GET).\n"
 "              Read  the  HTTP  1.1 specification for details and explanations.\n"
+, stdout);
+ fputs(
 "              Common additional HTTP requests  include  PUT  and  DELETE,  but\n"
 "              related technologies like WebDAV offers PROPFIND, COPY, MOVE and\n"
 "              more.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with FTP.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --xattr\n"
 "              When  saving  output  to a file, this option tells curl to store\n"
+, stdout);
+ fputs(
 "              certain file metadata in extened file attributes. Currently, the\n"
 "              URL is stored in the xdg.origin.url attribute and, for HTTP, the\n"
 "              content type is stored in the mime_type attribute. If  the  file\n"
 "              system  does  not  support  extended  attributes,  a  warning is\n"
-, stdout);
- fputs(
 "              issued.\n"
 "\n"
 "       -y, --speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
+, stdout);
+ fputs(
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -Y.\n"
 "\n"
 "              This option controls transfers and thus  will  not  affect  slow\n"
 "              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
+, stdout);
+ fputs(
 "              If a download is slower than this given speed (in bytes per sec-\n"
 "              ond)  for  speed-time seconds it gets aborted. speed-time is set\n"
 "              with -y and is 30 if not set.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z, --time-cond <date expression>\n"
-, stdout);
- fputs(
 "              (HTTP/FTP/FILE) Request a file that has been modified later than\n"
 "              the  given  time  and date, or one that has been modified before\n"
+, stdout);
+ fputs(
 "              that time. The date expression can be all sorts of date  strings\n"
 "              or  if  it  doesn't match any internal ones, it tries to get the\n"
 "              time from a given file name instead! See the curl_getdate(3) man\n"
 "              pages for date expression details.\n"
 "\n"
-, stdout);
- fputs(
 "              Start the date expression with a dash (-) to make it request for\n"
 "              a document that is older than the given date/time, default is  a\n"
-"              document that is newer than the specified date/time.\n"
+, stdout);
+ fputs(
+"              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -h, --help\n"
 "              Usage help.\n"
 "\n"
 "       -M, --manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -V, --version\n"
-, stdout);
- fputs(
 "              Displays information about curl and the libcurl version it uses.\n"
 "              The  first  line  includes the full version of curl, libcurl and\n"
+, stdout);
+ fputs(
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
 "              The second line (starts with \"Protocols:\") shows  all  protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
 "              The third line (starts with \"Features:\") shows specific features\n"
-, stdout);
- fputs(
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
 "              krb4   Krb4 for FTP is supported.\n"
 "\n"
 "              SSL    HTTPS and FTPS are supported.\n"
 "\n"
+, stdout);
+ fputs(
 "              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              GSS-Negotiate\n"
 "                     Negotiate authentication and krb5 for FTP is supported.\n"
 "\n"
-, stdout);
- fputs(
 "              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
 "                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
 "              AsynchDNS\n"
+, stdout);
+ fputs(
 "                     This curl uses asynchronous name resolves.\n"
 "\n"
 "              SPNEGO SPNEGO Negotiate authentication is supported.\n"
 "\n"
 "              Largefile\n"
 "                     This curl supports transfers of large files, files larger\n"
 "                     than 2GB.\n"
 "\n"
-, stdout);
- fputs(
 "              IDN    This curl supports IDN - international domain names.\n"
 "\n"
 "              SSPI   SSPI is supported. If you use NTLM and set a  blank  user\n"
+, stdout);
+ fputs(
 "                     name,  curl  will authenticate with your current user and\n"
 "                     password.\n"
 "\n"
 "              TLS-SRP\n"
 "                     SRP (Secure Remote Password) authentication is  supported\n"
 "                     for TLS.\n"
 "\n"
 "FILES\n"
 "       ~/.curlrc\n"
 "              Default config file, see -K, --config for details.\n"
 "\n"
 "ENVIRONMENT\n"
+"       The environment variables can be specified in lower case or upper case.\n"
 , stdout);
  fputs(
-"       The environment variables can be specified in lower case or upper case.\n"
 "       The lower case version has precedence. http_proxy is an exception as it\n"
 "       is only available in lower case.\n"
 "\n"
 "       Using  an  environment variable to set the proxy has the same effect as\n"
 "       using the --proxy option.\n"
 "\n"
 "       http_proxy [protocol://]<host>[:port]\n"
 "              Sets the proxy server to use for HTTP.\n"
 "       HTTPS_PROXY [protocol://]<host>[:port]\n"
-, stdout);
- fputs(
 "              Sets the proxy server to use for HTTPS.\n"
 "\n"
 "       [url-protocol]_PROXY [protocol://]<host>[:port]\n"
+, stdout);
+ fputs(
 "              Sets the proxy server to use for [url-protocol], where the  pro-\n"
 "              tocol  is  a  protocol  that curl supports and as specified in a\n"
 "              URL. FTP, FTPS, POP3, IMAP, SMTP, LDAP etc.\n"
 "\n"
 "       ALL_PROXY [protocol://]<host>[:port]\n"
 "              Sets the proxy server to use if no  protocol-specific  proxy  is\n"
 "              set.\n"
 "\n"
-, stdout);
- fputs(
 "       NO_PROXY <comma-separated list of hosts>\n"
 "              list  of  host names that shouldn't go through any proxy. If set\n"
+, stdout);
+ fputs(
 "              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "PROXY PROTOCOL PREFIXES\n"
 "       Since curl version 7.21.7, the proxy string may  be  specified  with  a\n"
 "       protocol:// prefix to specify alternative proxy protocols.\n"
 "\n"
 "       If  no  protocol  is  specified  in  the  proxy string or if the string\n"
-, stdout);
- fputs(
 "       doesn't match a supported one, the proxy will  be  treated  as  a  HTTP\n"
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
 "              Makes it the equivalent of --socks4a\n"
 "\n"
 "       socks5://\n"
 "              Makes it the equivalent of --socks5\n"
 "\n"
 "       socks5h://\n"
 "              Makes it the equivalent of --socks5-hostname\n"
 "\n"
 "EXIT CODES\n"
-, stdout);
- fputs(
 "       There  are  a  bunch  of  different error codes and their corresponding\n"
 "       error messages that may appear during bad conditions. At  the  time  of\n"
 "       this writing, the exit codes are:\n"
 "\n"
+, stdout);
+ fputs(
 "       1      Unsupported protocol. This build of curl has no support for this\n"
 "              protocol.\n"
 "\n"
 "       2      Failed to initialize.\n"
 "\n"
 "       3      URL malformed. The syntax was not correct.\n"
 "\n"
 "       4      A feature or option that  was  needed  to  perform  the  desired\n"
-, stdout);
- fputs(
 "              request  was  not  enabled  or was explicitly disabled at build-\n"
 "              time. To make curl able to do this, you  probably  need  another\n"
 "              build of libcurl!\n"
 "\n"
+, stdout);
+ fputs(
 "       5      Couldn't  resolve  proxy.  The  given  proxy  host  could not be\n"
 "              resolved.\n"
 "\n"
 "       6      Couldn't resolve host. The given remote host was not resolved.\n"
 "\n"
 "       7      Failed to connect to host.\n"
 "\n"
 "       8      FTP weird server reply.  The  server  sent  data  curl  couldn't\n"
-, stdout);
- fputs(
 "              parse.\n"
 "\n"
 "       9      FTP  access  denied. The server denied login or denied access to\n"
 "              the particular resource or directory you wanted to  reach.  Most\n"
+, stdout);
+ fputs(
 "              often  you  tried to change to a directory that doesn't exist on\n"
 "              the server.\n"
 "\n"
 "       11     FTP weird PASS reply. Curl couldn't parse the reply sent to  the\n"
 "              PASS request.\n"
 "\n"
 "       13     FTP  weird PASV reply, Curl couldn't parse the reply sent to the\n"
-, stdout);
- fputs(
 "              PASV request.\n"
 "\n"
 "       14     FTP weird 227 format.  Curl  couldn't  parse  the  227-line  the\n"
 "              server sent.\n"
 "\n"
+, stdout);
+ fputs(
 "       15     FTP  can't  get host. Couldn't resolve the host IP we got in the\n"
 "              227-line.\n"
 "\n"
 "       17     FTP couldn't set binary.  Couldn't  change  transfer  method  to\n"
 "              binary.\n"
 "\n"
 "       18     Partial file. Only a part of the file was transferred.\n"
 "\n"
 "       19     FTP  couldn't download/access the given file, the RETR (or simi-\n"
-, stdout);
- fputs(
 "              lar) command failed.\n"
 "\n"
 "       21     FTP quote error. A quote command returned error from the server.\n"
+, stdout);
+ fputs(
 "       22     HTTP page not retrieved. The requested  url  was  not  found  or\n"
 "              returned  another  error  with  the HTTP error code being 400 or\n"
 "              above. This return code only appears if -f, --fail is used.\n"
 "\n"
 "       23     Write error. Curl couldn't write data to a local  filesystem  or\n"
 "              similar.\n"
 "\n"
-, stdout);
- fputs(
 "       25     FTP  couldn't  STOR  file. The server denied the STOR operation,\n"
 "              used for FTP uploading.\n"
 "\n"
+, stdout);
+ fputs(
 "       26     Read error. Various reading problems.\n"
 "\n"
 "       27     Out of memory. A memory allocation request failed.\n"
 "\n"
 "       28     Operation timeout. The specified  time-out  period  was  reached\n"
 "              according to the conditions.\n"
 "\n"
 "       30     FTP  PORT  failed.  The PORT command failed. Not all FTP servers\n"
-, stdout);
- fputs(
 "              support the PORT  command,  try  doing  a  transfer  using  PASV\n"
 "              instead!\n"
 "\n"
+, stdout);
+ fputs(
 "       31     FTP  couldn't use REST. The REST command failed. This command is\n"
 "              used for resumed FTP transfers.\n"
 "\n"
 "       33     HTTP range error. The range \"command\" didn't work.\n"
 "\n"
 "       34     HTTP post error. Internal post-request generation error.\n"
 "\n"
 "       35     SSL connect error. The SSL handshaking failed.\n"
 "\n"
-, stdout);
- fputs(
 "       36     FTP bad download resume. Couldn't continue  an  earlier  aborted\n"
 "              download.\n"
 "\n"
+, stdout);
+ fputs(
 "       37     FILE couldn't read file. Failed to open the file. Permissions?\n"
 "\n"
 "       38     LDAP cannot bind. LDAP bind operation failed.\n"
 "\n"
 "       39     LDAP search failed.\n"
 "\n"
 "       41     Function not found. A required LDAP function was not found.\n"
 "\n"
 "       42     Aborted by callback. An application told curl to abort the oper-\n"
 "              ation.\n"
 "\n"
-, stdout);
- fputs(
 "       43     Internal error. A function was called with a bad parameter.\n"
 "\n"
+, stdout);
+ fputs(
 "       45     Interface error. A specified outgoing  interface  could  not  be\n"
 "              used.\n"
 "\n"
 "       47     Too many redirects. When following redirects, curl hit the maxi-\n"
 "              mum amount.\n"
 "\n"
 "       48     Unknown option specified to libcurl.  This  indicates  that  you\n"
 "              passed  a weird option to curl that was passed on to libcurl and\n"
 "              rejected. Read up in the manual!\n"
 "\n"
-, stdout);
- fputs(
 "       49     Malformed telnet option.\n"
 "\n"
+, stdout);
+ fputs(
 "       51     The peer's SSL certificate or SSH MD5 fingerprint was not OK.\n"
 "\n"
 "       52     The server didn't reply anything, which here  is  considered  an\n"
 "              error.\n"
 "\n"
 "       53     SSL crypto engine not found.\n"
