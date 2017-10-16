 "              All  operations that are performed over a HTTP proxy will trans-\n"
 "              parently be converted to HTTP. It means  that  certain  protocol\n"
 "              specific operations might not be available. This is not the case\n"
 "              if you can tunnel through the proxy, as one with the -p, --prox-\n"
 "              ytunnel option.\n"
 "\n"
-"              The  proxy host can be specified the exact same way as the proxy\n"
+"              User and password that might be provided in the proxy string are\n"
 , stdout);
  fputs(
+"              URL decoded by libcurl. This allows you to pass in special char-\n"
+"              acters such as @ by using %40 or pass in a colon with %3a.\n"
+"\n"
+"              The  proxy host can be specified the exact same way as the proxy\n"
 "              environment variables, including the protocol  prefix  (http://)\n"
 "              and the embedded user + password.\n"
 "\n"
 "              From  7.21.7,  the  proxy  string may be specified with a proto-\n"
+, stdout);
+ fputs(
 "              col://  prefix  to  specify  alternative  proxy  protocols.  Use\n"
 "              socks4://,  socks4a://,  socks5://  or socks5h:// to request the\n"
 "              specific SOCKS  version  to  be  used.  No  protocol  specified,\n"
-, stdout);
- fputs(
 "              http:// and all others will be treated as HTTP proxies.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X, --request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
+, stdout);
+ fputs(
 "              ing with the HTTP server.  The specified request  will  be  used\n"
 "              instead  of  the  method otherwise used (which defaults to GET).\n"
 "              Read the HTTP 1.1 specification for  details  and  explanations.\n"
-, stdout);
- fputs(
 "              Common  additional  HTTP  requests  include  PUT and DELETE, but\n"
 "              related technologies like WebDAV offers PROPFIND, COPY, MOVE and\n"
 "              more.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
+, stdout);
+ fputs(
 "              doing file lists with FTP.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --xattr\n"
 "              When saving output to a file, this option tells  curl  to  store\n"
-, stdout);
- fputs(
 "              certain file metadata in extened file attributes. Currently, the\n"
 "              URL is stored in the xdg.origin.url attribute and, for HTTP, the\n"
 "              content  type  is stored in the mime_type attribute. If the file\n"
+, stdout);
+ fputs(
 "              system does  not  support  extended  attributes,  a  warning  is\n"
 "              issued.\n"
 "\n"
 "       -y, --speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
-, stdout);
- fputs(
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -Y.\n"
 "\n"
 "              This  option  controls  transfers  and thus will not affect slow\n"
+, stdout);
+ fputs(
 "              connects etc. If this is a concern for you, try  the  --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
-, stdout);
- fputs(
 "              If a download is slower than this given speed (in bytes per sec-\n"
 "              ond) for speed-time seconds it gets aborted. speed-time  is  set\n"
 "              with -y and is 30 if not set.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-"       -z, --time-cond <date expression>\n"
-"              (HTTP/FTP/FILE) Request a file that has been modified later than\n"
-"              the given time and date, or one that has  been  modified  before\n"
+"       -z/--time-cond <date expression>|<file>\n"
+"              (HTTP/FTP)  Request a file that has been modified later than the\n"
+"              given time and date, or one that has been modified  before  that\n"
+"              time.  The <date expression> can be all sorts of date strings or\n"
+"              if it doesn't match any internal ones, it is taken as a filename\n"
 , stdout);
  fputs(
-"              that  time. The date expression can be all sorts of date strings\n"
-"              or if it doesn't match any internal ones, it tries  to  get  the\n"
-"              time from a given file name instead! See the curl_getdate(3) man\n"
-"              pages for date expression details.\n"
+"              and  tries  to  get  the  modification  date (mtime) from <file>\n"
+"              instead. See the curl_getdate(3) man pages for  date  expression\n"
+"              details.\n"
 "\n"
 "              Start the date expression with a dash (-) to make it request for\n"
-"              a  document that is older than the given date/time, default is a\n"
-, stdout);
- fputs(
+"              a document that is older than the given date/time, default is  a\n"
 "              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "       -h, --help\n"
 "              Usage help.\n"
 "\n"
 "       -M, --manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -V, --version\n"
 "              Displays information about curl and the libcurl version it uses.\n"
-"              The first line includes the full version of  curl,  libcurl  and\n"
-, stdout);
- fputs(
+"              The  first  line  includes the full version of curl, libcurl and\n"
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
-"              The  second  line (starts with \"Protocols:\") shows all protocols\n"
+"              The second line (starts with \"Protocols:\") shows  all  protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
+, stdout);
+ fputs(
 "              The third line (starts with \"Features:\") shows specific features\n"
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
 "              krb4   Krb4 for FTP is supported.\n"
 "\n"
 "              SSL    HTTPS and FTPS are supported.\n"
 "\n"
-, stdout);
- fputs(
-"              libz   Automatic  decompression of compressed files over HTTP is\n"
+"              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              GSS-Negotiate\n"
+, stdout);
+ fputs(
 "                     Negotiate authentication and krb5 for FTP is supported.\n"
 "\n"
-"              Debug  This curl uses a libcurl built with Debug.  This  enables\n"
-"                     more  error-tracking  and memory debugging etc. For curl-\n"
+"              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
+"                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
 "              AsynchDNS\n"
-, stdout);
- fputs(
 "                     This curl uses asynchronous name resolves.\n"
 "\n"
 "              SPNEGO SPNEGO Negotiate authentication is supported.\n"
 "\n"
 "              Largefile\n"
+, stdout);
+ fputs(
 "                     This curl supports transfers of large files, files larger\n"
 "                     than 2GB.\n"
 "\n"
 "              IDN    This curl supports IDN - international domain names.\n"
 "\n"
-"              SSPI   SSPI  is  supported. If you use NTLM and set a blank user\n"
-, stdout);
- fputs(
-"                     name, curl will authenticate with your current  user  and\n"
+"              SSPI   SSPI is supported. If you use NTLM and set a  blank  user\n"
+"                     name,  curl  will authenticate with your current user and\n"
 "                     password.\n"
 "\n"
 "              TLS-SRP\n"
-"                     SRP  (Secure Remote Password) authentication is supported\n"
+"                     SRP (Secure Remote Password) authentication is  supported\n"
+, stdout);
+ fputs(
 "                     for TLS.\n"
 "\n"
 "FILES\n"
 "       ~/.curlrc\n"
 "              Default config file, see -K, --config for details.\n"
 "\n"
 "ENVIRONMENT\n"
 "       The environment variables can be specified in lower case or upper case.\n"
-, stdout);
- fputs(
 "       The lower case version has precedence. http_proxy is an exception as it\n"
 "       is only available in lower case.\n"
 "\n"
-"       Using an environment variable to set the proxy has the same  effect  as\n"
+"       Using  an  environment variable to set the proxy has the same effect as\n"
 "       using the --proxy option.\n"
 "\n"
 "       http_proxy [protocol://]<host>[:port]\n"
+, stdout);
+ fputs(
 "              Sets the proxy server to use for HTTP.\n"
 "       HTTPS_PROXY [protocol://]<host>[:port]\n"
 "              Sets the proxy server to use for HTTPS.\n"
 "\n"
 "       [url-protocol]_PROXY [protocol://]<host>[:port]\n"
-, stdout);
- fputs(
-"              Sets  the proxy server to use for [url-protocol], where the pro-\n"
-"              tocol is a protocol that curl supports and  as  specified  in  a\n"
+"              Sets the proxy server to use for [url-protocol], where the  pro-\n"
+"              tocol  is  a  protocol  that curl supports and as specified in a\n"
 "              URL. FTP, FTPS, POP3, IMAP, SMTP, LDAP etc.\n"
 "\n"
 "       ALL_PROXY [protocol://]<host>[:port]\n"
-"              Sets  the  proxy  server to use if no protocol-specific proxy is\n"
+, stdout);
+ fputs(
+"              Sets the proxy server to use if no  protocol-specific  proxy  is\n"
 "              set.\n"
 "\n"
 "       NO_PROXY <comma-separated list of hosts>\n"
-"              list of host names that shouldn't go through any proxy.  If  set\n"
-, stdout);
- fputs(
+"              list  of  host names that shouldn't go through any proxy. If set\n"
 "              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "PROXY PROTOCOL PREFIXES\n"
-"       Since  curl  version  7.21.7,  the proxy string may be specified with a\n"
+"       Since curl version 7.21.7, the proxy string may  be  specified  with  a\n"
 "       protocol:// prefix to specify alternative proxy protocols.\n"
 "\n"
-"       If no protocol is specified in  the  proxy  string  or  if  the  string\n"
-"       doesn't  match  a  supported  one,  the proxy will be treated as a HTTP\n"
+, stdout);
+ fputs(
+"       If  no  protocol  is  specified  in  the  proxy string or if the string\n"
+"       doesn't match a supported one, the proxy will  be  treated  as  a  HTTP\n"
 "       proxy.\n"
 "\n"
 "       The supported proxy protocol prefixes are as follows:\n"
 "\n"
 "       socks4://\n"
-, stdout);
- fputs(
 "              Makes it the equivalent of --socks4\n"
 "\n"
 "       socks4a://\n"
 "              Makes it the equivalent of --socks4a\n"
 "\n"
 "       socks5://\n"
 "              Makes it the equivalent of --socks5\n"
 "\n"
 "       socks5h://\n"
+, stdout);
+ fputs(
 "              Makes it the equivalent of --socks5-hostname\n"
 "\n"
 "EXIT CODES\n"
-"       There are a bunch of different  error  codes  and  their  corresponding\n"
-"       error  messages  that  may appear during bad conditions. At the time of\n"
+"       There  are  a  bunch  of  different error codes and their corresponding\n"
+"       error messages that may appear during bad conditions. At  the  time  of\n"
 "       this writing, the exit codes are:\n"
 "\n"
-, stdout);
- fputs(
 "       1      Unsupported protocol. This build of curl has no support for this\n"
 "              protocol.\n"
 "\n"
 "       2      Failed to initialize.\n"
 "\n"
 "       3      URL malformed. The syntax was not correct.\n"
 "\n"
-"       4      A  feature  or  option  that  was  needed to perform the desired\n"
-"              request was not enabled or was  explicitly  disabled  at  build-\n"
-"              time.  To  make  curl able to do this, you probably need another\n"
-"              build of libcurl!\n"
-"\n"
 , stdout);
  fputs(
-"       5      Couldn't resolve proxy.  The  given  proxy  host  could  not  be\n"
+"       4      A feature or option that  was  needed  to  perform  the  desired\n"
+"              request  was  not  enabled  or was explicitly disabled at build-\n"
+"              time. To make curl able to do this, you  probably  need  another\n"
+"              build of libcurl!\n"
+"\n"
+"       5      Couldn't  resolve  proxy.  The  given  proxy  host  could not be\n"
 "              resolved.\n"
 "\n"
 "       6      Couldn't resolve host. The given remote host was not resolved.\n"
 "\n"
 "       7      Failed to connect to host.\n"
 "\n"
-"       8      FTP  weird  server  reply.  The  server  sent data curl couldn't\n"
-"              parse.\n"
-"\n"
-"       9      FTP access denied. The server denied login or denied  access  to\n"
-"              the  particular  resource or directory you wanted to reach. Most\n"
 , stdout);
  fputs(
-"              often you tried to change to a directory that doesn't  exist  on\n"
+"       8      FTP weird server reply.  The  server  sent  data  curl  couldn't\n"
+"              parse.\n"
+"\n"
+"       9      FTP  access  denied. The server denied login or denied access to\n"
+"              the particular resource or directory you wanted to  reach.  Most\n"
+"              often  you  tried to change to a directory that doesn't exist on\n"
 "              the server.\n"
 "\n"
-"       11     FTP  weird PASS reply. Curl couldn't parse the reply sent to the\n"
+"       11     FTP weird PASS reply. Curl couldn't parse the reply sent to  the\n"
 "              PASS request.\n"
 "\n"
-"       13     FTP weird PASV reply, Curl couldn't parse the reply sent to  the\n"
+, stdout);
+ fputs(
+"       13     FTP  weird PASV reply, Curl couldn't parse the reply sent to the\n"
 "              PASV request.\n"
 "\n"
-"       14     FTP  weird  227  format.  Curl  couldn't  parse the 227-line the\n"
+"       14     FTP weird 227 format.  Curl  couldn't  parse  the  227-line  the\n"
 "              server sent.\n"
 "\n"
-, stdout);
- fputs(
-"       15     FTP can't get host. Couldn't resolve the host IP we got  in  the\n"
+"       15     FTP  can't  get host. Couldn't resolve the host IP we got in the\n"
 "              227-line.\n"
 "\n"
-"       17     FTP  couldn't  set  binary.  Couldn't  change transfer method to\n"
+"       17     FTP couldn't set binary.  Couldn't  change  transfer  method  to\n"
 "              binary.\n"
 "\n"
 "       18     Partial file. Only a part of the file was transferred.\n"
 "\n"
-"       19     FTP couldn't download/access the given file, the RETR (or  simi-\n"
+, stdout);
+ fputs(
+"       19     FTP  couldn't download/access the given file, the RETR (or simi-\n"
 "              lar) command failed.\n"
 "\n"
 "       21     FTP quote error. A quote command returned error from the server.\n"
-, stdout);
- fputs(
-"       22     HTTP  page  not  retrieved.  The  requested url was not found or\n"
-"              returned another error with the HTTP error  code  being  400  or\n"
+"       22     HTTP page not retrieved. The requested  url  was  not  found  or\n"
+"              returned  another  error  with  the HTTP error code being 400 or\n"
 "              above. This return code only appears if -f, --fail is used.\n"
 "\n"
-"       23     Write  error.  Curl couldn't write data to a local filesystem or\n"
+, stdout);
+ fputs(
+"       23     Write error. Curl couldn't write data to a local  filesystem  or\n"
 "              similar.\n"
 "\n"
-"       25     FTP couldn't STOR file. The server denied  the  STOR  operation,\n"
+"       25     FTP  couldn't  STOR  file. The server denied the STOR operation,\n"
 "              used for FTP uploading.\n"
 "\n"
-, stdout);
- fputs(
 "       26     Read error. Various reading problems.\n"
 "\n"
 "       27     Out of memory. A memory allocation request failed.\n"
 "\n"
-"       28     Operation  timeout.  The  specified  time-out period was reached\n"
+"       28     Operation timeout. The specified  time-out  period  was  reached\n"
 "              according to the conditions.\n"
 "\n"
-"       30     FTP PORT failed. The PORT command failed. Not  all  FTP  servers\n"
-"              support  the  PORT  command,  try  doing  a  transfer using PASV\n"
-"              instead!\n"
-"\n"
 , stdout);
  fputs(
-"       31     FTP couldn't use REST. The REST command failed. This command  is\n"
+"       30     FTP  PORT  failed.  The PORT command failed. Not all FTP servers\n"
+"              support the PORT  command,  try  doing  a  transfer  using  PASV\n"
+"              instead!\n"
+"\n"
+"       31     FTP  couldn't use REST. The REST command failed. This command is\n"
 "              used for resumed FTP transfers.\n"
 "\n"
 "       33     HTTP range error. The range \"command\" didn't work.\n"
 "\n"
 "       34     HTTP post error. Internal post-request generation error.\n"
 "\n"
+, stdout);
+ fputs(
 "       35     SSL connect error. The SSL handshaking failed.\n"
 "\n"
-"       36     FTP  bad  download  resume. Couldn't continue an earlier aborted\n"
+"       36     FTP bad download resume. Couldn't continue  an  earlier  aborted\n"
 "              download.\n"
 "\n"
-, stdout);
- fputs(
 "       37     FILE couldn't read file. Failed to open the file. Permissions?\n"
 "\n"
 "       38     LDAP cannot bind. LDAP bind operation failed.\n"
 "\n"
 "       39     LDAP search failed.\n"
 "\n"
 "       41     Function not found. A required LDAP function was not found.\n"
 "\n"
 "       42     Aborted by callback. An application told curl to abort the oper-\n"
+, stdout);
+ fputs(
 "              ation.\n"
 "\n"
 "       43     Internal error. A function was called with a bad parameter.\n"
 "\n"
-, stdout);
- fputs(
-"       45     Interface  error.  A  specified  outgoing interface could not be\n"
+"       45     Interface error. A specified outgoing  interface  could  not  be\n"
 "              used.\n"
 "\n"
 "       47     Too many redirects. When following redirects, curl hit the maxi-\n"
 "              mum amount.\n"
 "\n"
-"       48     Unknown  option  specified  to  libcurl. This indicates that you\n"
-"              passed a weird option to curl that was passed on to libcurl  and\n"
+"       48     Unknown option specified to libcurl.  This  indicates  that  you\n"
+"              passed  a weird option to curl that was passed on to libcurl and\n"
+, stdout);
+ fputs(
 "              rejected. Read up in the manual!\n"
 "\n"
 "       49     Malformed telnet option.\n"
 "\n"
-, stdout);
- fputs(
 "       51     The peer's SSL certificate or SSH MD5 fingerprint was not OK.\n"
 "\n"
-"       52     The  server  didn't  reply anything, which here is considered an\n"
+"       52     The server didn't reply anything, which here  is  considered  an\n"
 "              error.\n"
 "\n"
 "       53     SSL crypto engine not found.\n"
 "\n"
 "       54     Cannot set SSL crypto engine as default.\n"
 "\n"
 "       55     Failed sending network data.\n"
 "\n"
 "       56     Failure in receiving network data.\n"
 "\n"
+, stdout);
+ fputs(
 "       58     Problem with the local certificate.\n"
 "\n"
 "       59     Couldn't use specified SSL cipher.\n"
 "\n"
-, stdout);
- fputs(
-"       60     Peer certificate cannot be authenticated with known CA  certifi-\n"
+"       60     Peer  certificate cannot be authenticated with known CA certifi-\n"
 "              cates.\n"
 "\n"
 "       61     Unrecognized transfer encoding.\n"
 "\n"
 "       62     Invalid LDAP URL.\n"
 "\n"
