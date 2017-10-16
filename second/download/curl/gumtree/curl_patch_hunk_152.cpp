 "              protocol specific operations might not be available. This is not\n"
 "              the case if you can tunnel through the proxy, as done  with  the\n"
 "              -p/--proxytunnel option.\n"
 "\n"
 , stdout);
  fputs(
+"              Starting  with 7.14.1, the proxy host can be specified the exact\n"
+"              same way as the proxy environment  variables,  include  protocol\n"
+"              prefix (http://) and embedded user + password.\n"
+"\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X/--request <command>\n"
-"              (HTTP) Specifies a custom request to use when communicating with\n"
-"              the  HTTP server.  The specified request will be used instead of\n"
-"              the standard GET. Read the HTTP 1.1  specification  for  details\n"
-"              and explanations.\n"
+"              (HTTP) Specifies a custom request method to use when communicat-\n"
+"              ing  with  the  HTTP server.  The specified request will be used\n"
+, stdout);
+ fputs(
+"              instead of the method otherwise used (which  defaults  to  GET).\n"
+"              Read the HTTP 1.1 specification for details and explanations.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with ftp.\n"
-, stdout);
- fputs(
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -y/--speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
+, stdout);
+ fputs(
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -y.\n"
 "\n"
 "              This  option  controls  transfers  and thus will not affect slow\n"
-, stdout);
- fputs(
 "              connects etc. If this is a concern for you, try  the  --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y/--speed-limit <speed>\n"
+, stdout);
+ fputs(
 "              If a download is slower than this given speed, in bytes per sec-\n"
 "              ond,  for  speed-time seconds it gets aborted. speed-time is set\n"
 "              with -Y and is 30 if not set.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z/--time-cond <date expression>\n"
 "              (HTTP)  Request  a  file  that  has been modified later than the\n"
 "              given time and date, or one that has been modified  before  that\n"
-"              time. The date expression can be all sorts of date strings or if\n"
-"              it doesn't match any internal ones, it tries  to  get  the  time\n"
 , stdout);
  fputs(
+"              time. The date expression can be all sorts of date strings or if\n"
+"              it doesn't match any internal ones, it tries  to  get  the  time\n"
 "              from  a  given  file  name  instead! See the curl_getdate(3) man\n"
 "              pages for date expression details.\n"
 "\n"
 "              Start the date expression with a dash (-) to make it request for\n"
 "              a  document that is older than the given date/time, default is a\n"
+, stdout);
+ fputs(
 "              document that is newer than the specified date/time.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --max-redirs <num>\n"
-, stdout);
- fputs(
 "              Set   maximum   number  of  redirection-followings  allowed.  If\n"
 "              -L/--location is used, this option can be used to  prevent  curl\n"
 "              from following redirections \"in absurdum\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -0/--http1.0\n"
+, stdout);
+ fputs(
 "              (HTTP) Forces curl to issue its requests using HTTP 1.0  instead\n"
 "              of using its internally preferred: HTTP 1.1.\n"
 "\n"
 "       -1/--tlsv1\n"
-, stdout);
- fputs(
 "              (HTTPS) Forces curl to use TSL version 1 when negotiating with a\n"
 "              remote TLS server.\n"
 "\n"
 "       -2/--sslv2\n"
 "              (HTTPS) Forces curl to use SSL version 2 when negotiating with a\n"
 "              remote SSL server.\n"
 "\n"
 "       -3/--sslv3\n"
 "              (HTTPS) Forces curl to use SSL version 3 when negotiating with a\n"
+, stdout);
+ fputs(
 "              remote SSL server.\n"
 "\n"
 "       --3p-quote\n"
 "              (FTP) Specify arbitrary commands to send to the  source  server.\n"
-, stdout);
- fputs(
 "              See the -Q/--quote option for details. (Added in 7.13.0)\n"
 "\n"
 "       --3p-url\n"
 "              (FTP)  Activates  a FTP 3rd party transfer. Specifies the source\n"
 "              URL to get a file from, while the \"normal\" URL will be  used  as\n"
 "              target URL, the file that will be written/created.\n"
 "\n"
+, stdout);
+ fputs(
 "              Note  that  not all FTP server allow 3rd party transfers. (Added\n"
 "              in 7.13.0)\n"
 "\n"
 "       --3p-user\n"
-, stdout);
- fputs(
 "              (FTP) Specify user:password for the source URL transfer.  (Added\n"
 "              in 7.13.0)\n"
 "\n"
 "       -4/--ipv4\n"
 "              If  libcurl  is  capable  of resolving an address to multiple IP\n"
 "              versions (which it is if it is ipv6-capable), this option  tells\n"
 "              libcurl  to  resolve  names  to  IPv4  addresses only. (Added in\n"
+, stdout);
+ fputs(
 "              7.10.8)\n"
 "\n"
 "       -6/--ipv6\n"
 "              If libcurl is capable of resolving an  address  to  multiple  IP\n"
-, stdout);
- fputs(
 "              versions  (which it is if it is ipv6-capable), this option tells\n"
 "              libcurl to resolve names  to  IPv6  addresses  only.  (Added  in\n"
 "              7.10.8)\n"
 "\n"
 "       -#/--progress-bar\n"
 "              Make curl display progress information as a progress bar instead\n"
 "              of the default statistics.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used twice, the second will again disable  the\n"
 "              progress bar.\n"
 "\n"
 "FILES\n"
 "       ~/.curlrc\n"
 "              Default config file.\n"
 "\n"
-, stdout);
- fputs(
 "ENVIRONMENT\n"
 "       http_proxy [protocol://]<host>[:port]\n"
 "              Sets proxy server to use for HTTP.\n"
 "\n"
 "       HTTPS_PROXY [protocol://]<host>[:port]\n"
 "              Sets proxy server to use for HTTPS.\n"
 "\n"
 "       FTP_PROXY [protocol://]<host>[:port]\n"
 "              Sets proxy server to use for FTP.\n"
 "\n"
+, stdout);
+ fputs(
 "       GOPHER_PROXY [protocol://]<host>[:port]\n"
 "              Sets proxy server to use for GOPHER.\n"
 "       ALL_PROXY [protocol://]<host>[:port]\n"
-, stdout);
- fputs(
 "              Sets proxy server to use if no protocol-specific proxy is set.\n"
 "\n"
 "       NO_PROXY <comma-separated list of hosts>\n"
 "              list  of  host names that shouldn't go through any proxy. If set\n"
-"              to a asterisk\n"
+"              to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "EXIT CODES\n"
 "       There exists a bunch of different error codes and  their  corresponding\n"
+, stdout);
+ fputs(
 "       error  messages  that  may appear during bad conditions. At the time of\n"
 "       this writing, the exit codes are:\n"
 "\n"
-, stdout);
- fputs(
 "       1      Unsupported protocol. This build of curl has no support for this\n"
 "              protocol.\n"
 "\n"
 "       2      Failed to initialize.\n"
 "\n"
 "       3      URL malformat. The syntax was not correct.\n"
 "\n"
 "       4      URL  user  malformatted. The user-part of the URL syntax was not\n"
 "              correct.\n"
 "\n"
+, stdout);
+ fputs(
 "       5      Couldn't resolve proxy.  The  given  proxy  host  could  not  be\n"
 "              resolved.\n"
 "\n"
 "       6      Couldn't resolve host. The given remote host was not resolved.\n"
 "\n"
-, stdout);
- fputs(
 "       7      Failed to connect to host.\n"
 "\n"
 "       8      FTP  weird  server  reply.  The  server  sent data curl couldn't\n"
 "              parse.\n"
 "\n"
 "       9      FTP access denied. The server denied login.\n"
 "\n"
 "       10     FTP  user/password  incorrect.  Either  one  or  both  were  not\n"
+, stdout);
+ fputs(
 "              accepted by the server.\n"
 "\n"
 "       11     FTP  weird PASS reply. Curl couldn't parse the reply sent to the\n"
 "              PASS request.\n"
 "\n"
-, stdout);
- fputs(
 "       12     FTP weird USER reply. Curl couldn't parse the reply sent to  the\n"
 "              USER request.\n"
 "\n"
 "       13     FTP  weird PASV reply, Curl couldn't parse the reply sent to the\n"
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
-, stdout);
- fputs(
 "       16     FTP can't reconnect. Couldn't connect to the host we got in  the\n"
 "              227-line.\n"
 "\n"
 "       17     FTP  couldn't  set  binary.  Couldn't  change transfer method to\n"
 "              binary.\n"
 "\n"
 "       18     Partial file. Only a part of the file was transferred.\n"
 "\n"
 "       19     FTP couldn't download/access the given file, the RETR (or  simi-\n"
 "              lar) command failed.\n"
 "\n"
-"       20     FTP write error. The transfer was reported bad by the server.\n"
-"\n"
 , stdout);
  fputs(
+"       20     FTP write error. The transfer was reported bad by the server.\n"
+"\n"
 "       21     FTP quote error. A quote command returned error from the server.\n"
 "       22     HTTP page not retrieved. The requested  url  was  not  found  or\n"
 "              returned  another  error  with  the HTTP error code being 400 or\n"
 "              above. This return code only appears if -f/--fail is used.\n"
 "\n"
 "       23     Write error. Curl couldn't write data to a local  filesystem  or\n"
 "              similar.\n"
 "\n"
-"       24     Malformed user. User name badly specified.\n"
-"\n"
 , stdout);
  fputs(
+"       24     Malformed user. User name badly specified.\n"
+"\n"
 "       25     FTP  couldn't  STOR  file. The server denied the STOR operation,\n"
 "              used for FTP uploading.\n"
 "\n"
 "       26     Read error. Various reading problems.\n"
 "\n"
 "       27     Out of memory. A memory allocation request failed.\n"
