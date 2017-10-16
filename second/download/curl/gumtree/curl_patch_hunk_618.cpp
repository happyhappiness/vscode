 "              doing file lists with FTP.\n"
 "\n"
 , stdout);
  fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+"       --xattr\n"
+"              When  saving  output  to a file, this option tells curl to store\n"
+"              certain file metadata in extened file attributes. Currently, the\n"
+"              URL is stored in the xdg.origin.url attribute and, for HTTP, the\n"
+"              content type is stored in the mime_type attribute. If  the  file\n"
+"              system  does  not  support  extended  attributes,  a  warning is\n"
+, stdout);
+ fputs(
+"              issued.\n"
+"\n"
 "       -y, --speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -Y.\n"
 "\n"
-"              This  option  controls  transfers  and thus will not affect slow\n"
-, stdout);
- fputs(
-"              connects etc. If this is a concern for you, try  the  --connect-\n"
+"              This option controls transfers and thus  will  not  affect  slow\n"
+"              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y, --speed-limit <speed>\n"
 "              If a download is slower than this given speed (in bytes per sec-\n"
-"              ond) for speed-time seconds it gets aborted. speed-time  is  set\n"
+"              ond)  for  speed-time seconds it gets aborted. speed-time is set\n"
 "              with -y and is 30 if not set.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z, --time-cond <date expression>\n"
-"              (HTTP/FTP/FILE) Request a file that has been modified later than\n"
-"              the given time and date, or one that has  been  modified  before\n"
-"              that  time. The date expression can be all sorts of date strings\n"
-"              or if it doesn't match any internal ones, it tries  to  get  the\n"
 , stdout);
  fputs(
+"              (HTTP/FTP/FILE) Request a file that has been modified later than\n"
+"              the  given  time  and date, or one that has been modified before\n"
+"              that time. The date expression can be all sorts of date  strings\n"
+"              or  if  it  doesn't match any internal ones, it tries to get the\n"
 "              time from a given file name instead! See the curl_getdate(3) man\n"
 "              pages for date expression details.\n"
 "\n"
+, stdout);
+ fputs(
 "              Start the date expression with a dash (-) to make it request for\n"
-"              a  document that is older than the given date/time, default is a\n"
+"              a document that is older than the given date/time, default is  a\n"
 "              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -h, --help\n"
 "              Usage help.\n"
 "\n"
 "       -M, --manual\n"
-, stdout);
- fputs(
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -V, --version\n"
+, stdout);
+ fputs(
 "              Displays information about curl and the libcurl version it uses.\n"
-"              The first line includes the full version of  curl,  libcurl  and\n"
+"              The  first  line  includes the full version of curl, libcurl and\n"
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
-"              The  second  line (starts with \"Protocols:\") shows all protocols\n"
+"              The second line (starts with \"Protocols:\") shows  all  protocols\n"
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
 "              SSL    HTTPS and FTPS are supported.\n"
 "\n"
-"              libz   Automatic  decompression of compressed files over HTTP is\n"
+"              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              GSS-Negotiate\n"
-, stdout);
- fputs(
 "                     Negotiate authentication and krb5 for FTP is supported.\n"
 "\n"
-"              Debug  This curl uses a libcurl built with Debug.  This  enables\n"
-"                     more  error-tracking  and memory debugging etc. For curl-\n"
+, stdout);
+ fputs(
+"              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
+"                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
 "              AsynchDNS\n"
 "                     This curl uses asynchronous name resolves.\n"
 "\n"
 "              SPNEGO SPNEGO Negotiate authentication is supported.\n"
 "\n"
 "              Largefile\n"
-, stdout);
- fputs(
 "                     This curl supports transfers of large files, files larger\n"
 "                     than 2GB.\n"
 "\n"
+, stdout);
+ fputs(
 "              IDN    This curl supports IDN - international domain names.\n"
 "\n"
-"              SSPI   SSPI  is  supported. If you use NTLM and set a blank user\n"
-"                     name, curl will authenticate with your current  user  and\n"
+"              SSPI   SSPI is supported. If you use NTLM and set a  blank  user\n"
+"                     name,  curl  will authenticate with your current user and\n"
 "                     password.\n"
 "\n"
 "              TLS-SRP\n"
-"                     SRP  (Secure Remote Password) authentication is supported\n"
-, stdout);
- fputs(
+"                     SRP (Secure Remote Password) authentication is  supported\n"
 "                     for TLS.\n"
 "\n"
 "FILES\n"
 "       ~/.curlrc\n"
 "              Default config file, see -K, --config for details.\n"
 "\n"
 "ENVIRONMENT\n"
+, stdout);
+ fputs(
 "       The environment variables can be specified in lower case or upper case.\n"
 "       The lower case version has precedence. http_proxy is an exception as it\n"
 "       is only available in lower case.\n"
 "\n"
-"       Using an environment variable to set the proxy has the same  effect  as\n"
+"       Using  an  environment variable to set the proxy has the same effect as\n"
 "       using the --proxy option.\n"
 "\n"
 "       http_proxy [protocol://]<host>[:port]\n"
-, stdout);
- fputs(
 "              Sets the proxy server to use for HTTP.\n"
 "       HTTPS_PROXY [protocol://]<host>[:port]\n"
+, stdout);
+ fputs(
 "              Sets the proxy server to use for HTTPS.\n"
 "\n"
 "       [url-protocol]_PROXY [protocol://]<host>[:port]\n"
-"              Sets  the proxy server to use for [url-protocol], where the pro-\n"
-"              tocol is a protocol that curl supports and  as  specified  in  a\n"
+"              Sets the proxy server to use for [url-protocol], where the  pro-\n"
+"              tocol  is  a  protocol  that curl supports and as specified in a\n"
 "              URL. FTP, FTPS, POP3, IMAP, SMTP, LDAP etc.\n"
 "\n"
 "       ALL_PROXY [protocol://]<host>[:port]\n"
-, stdout);
- fputs(
-"              Sets  the  proxy  server to use if no protocol-specific proxy is\n"
+"              Sets the proxy server to use if no  protocol-specific  proxy  is\n"
 "              set.\n"
 "\n"
+, stdout);
+ fputs(
 "       NO_PROXY <comma-separated list of hosts>\n"
-"              list of host names that shouldn't go through any proxy.  If  set\n"
+"              list  of  host names that shouldn't go through any proxy. If set\n"
 "              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "PROXY PROTOCOL PREFIXES\n"
-"       Since  curl  version  7.21.7,  the proxy string may be specified with a\n"
+"       Since curl version 7.21.7, the proxy string may  be  specified  with  a\n"
 "       protocol:// prefix to specify alternative proxy protocols.\n"
 "\n"
+"       If  no  protocol  is  specified  in  the  proxy string or if the string\n"
 , stdout);
  fputs(
-"       If no protocol is specified in  the  proxy  string  or  if  the  string\n"
-"       doesn't  match  a  supported  one,  the proxy will be treated as a HTTP\n"
+"       doesn't match a supported one, the proxy will  be  treated  as  a  HTTP\n"
 "       proxy.\n"
 "\n"
 "       The supported proxy protocol prefixes are as follows:\n"
 "\n"
 "       socks4://\n"
 "              Makes it the equivalent of --socks4\n"
