 "              Available variables are at this point:\n"
 "\n"
 "              url_effective  The URL that was fetched  last.  This  is  mostly\n"
 "                             meaningful  if  you've  told curl to follow loca-\n"
 "                             tion: headers.\n"
 "\n"
-"              http_code      The numerical code that was  found  in  the  last\n"
-"                             retrieved HTTP(S) page.\n"
-"\n"
-"              http_connect   The  numerical  code  that  was found in the last\n"
+"              http_code      The numerical response code that was found in the\n"
+"                             last  retrieved  HTTP(S)  or  FTP(s) transfer. In\n"
+"                             7.18.2 the alias response_code was added to  show\n"
 , stdout);
  fputs(
+"                             the same info.\n"
+"\n"
+"              http_connect   The  numerical  code  that  was found in the last\n"
 "                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 "                             request. (Added in 7.12.4)\n"
 "\n"
 "              time_total     The  total time, in seconds, that the full opera-\n"
 "                             tion lasted. The time will be displayed with mil-\n"
 "                             lisecond resolution.\n"
 "\n"
 "              time_namelookup\n"
-"                             The  time,  in  seconds,  it  took from the start\n"
 , stdout);
  fputs(
+"                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the name resolving was completed.\n"
 "\n"
 "              time_connect   The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  connect to the remote host (or proxy)\n"
 "                             was completed.\n"
 "\n"
 "              time_pretransfer\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
-"                             until  the  file transfer is just about to begin.\n"
 , stdout);
  fputs(
+"                             until  the  file transfer is just about to begin.\n"
 "                             This includes all pre-transfer commands and nego-\n"
 "                             tiations that are specific to the particular pro-\n"
 "                             tocol(s) involved.\n"
 "\n"
 "              time_redirect  The time, in seconds, it took for all redirection\n"
 "                             steps  include  name lookup, connect, pretransfer\n"
-"                             and  transfer  before   final   transaction   was\n"
 , stdout);
  fputs(
+"                             and  transfer  before   final   transaction   was\n"
 "                             started.  time_redirect shows the complete execu-\n"
 "                             tion time for multiple  redirections.  (Added  in\n"
 "                             7.12.3)\n"
 "\n"
 "              time_starttransfer\n"
 "                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the first byte is just about to  be  trans-\n"
-"                             ferred.  This  includes time_pretransfer and also\n"
 , stdout);
  fputs(
+"                             ferred.  This  includes time_pretransfer and also\n"
 "                             the  time  the  server  needs  to  calculate  the\n"
 "                             result.\n"
 "\n"
 "              size_download  The total amount of bytes that were downloaded.\n"
 "\n"
 "              size_upload    The total amount of bytes that were uploaded.\n"
 "\n"
 "              size_header    The total amount of bytes of the downloaded head-\n"
 "                             ers.\n"
 "\n"
-"              size_request   The total amount of bytes that were sent  in  the\n"
 , stdout);
  fputs(
+"              size_request   The total amount of bytes that were sent  in  the\n"
 "                             HTTP request.\n"
 "\n"
 "              speed_download The average download speed that curl measured for\n"
 "                             the complete download.\n"
 "\n"
 "              speed_upload   The average upload speed that curl  measured  for\n"
 "                             the complete upload.\n"
 "\n"
 "              content_type   The  Content-Type  of  the requested document, if\n"
-"                             there was any.\n"
-"\n"
 , stdout);
  fputs(
+"                             there was any.\n"
+"\n"
 "              num_connects   Number of new connects made in the recent  trans-\n"
 "                             fer. (Added in 7.12.3)\n"
 "\n"
 "              num_redirects  Number  of  redirects  that  were followed in the\n"
 "                             request. (Added in 7.12.3)\n"
 "\n"
+"              redirect_url   When a HTTP request was made without -L to follow\n"
+"                             redirects, this variable will show the actual URL\n"
+, stdout);
+ fputs(
+"                             a redirect would take you to. (Added in 7.18.2)\n"
+"\n"
 "              ftp_entry_path The initial path libcurl ended up in when logging\n"
 "                             on to the remote FTP server. (Added in 7.15.4)\n"
 "\n"
 "       If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       -x/--proxy <proxyhost[:port]>\n"
 "              Use  specified  HTTP proxy. If the port number is not specified,\n"
 "              it is assumed at port 1080.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides existing environment variables  that  sets\n"
 "              proxy  to  use.  If  there's  an  environment variable setting a\n"
 "              proxy, you can set proxy to \"\" to override it.\n"
 "\n"
 "              Note that all operations that are performed over  a  HTTP  proxy\n"
-, stdout);
- fputs(
 "              will  transparently  be converted to HTTP. It means that certain\n"
 "              protocol specific operations might not be available. This is not\n"
+, stdout);
+ fputs(
 "              the  case  if you can tunnel through the proxy, as done with the\n"
 "              -p/--proxytunnel option.\n"
 "\n"
 "              Starting with 7.14.1, the proxy host can be specified the  exact\n"
 "              same  way  as  the proxy environment variables, include protocol\n"
 "              prefix (http://) and embedded user + password.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X/--request <command>\n"
+, stdout);
+ fputs(
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
 "              ing with the HTTP server.  The specified request  will  be  used\n"
 "              instead  of  the  method otherwise used (which defaults to GET).\n"
 "              Read the HTTP 1.1 specification for details and explanations.\n"
 "\n"
-, stdout);
- fputs(
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with ftp.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -y/--speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
 "              a speed-time period, the download gets aborted. If speed-time is\n"
 "              used, the default speed-limit will be 1 unless set with -y.\n"
 "\n"
+"              This option controls transfers and thus  will  not  affect  slow\n"
 , stdout);
  fputs(
-"              This option controls transfers and thus  will  not  affect  slow\n"
 "              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y/--speed-limit <speed>\n"
 "              If a download is slower than this given speed, in bytes per sec-\n"
 "              ond, for speed-time seconds it gets aborted. speed-time  is  set\n"
-, stdout);
- fputs(
 "              with -Y and is 30 if not set.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z/--time-cond <date expression>\n"
 "              (HTTP/FTP) Request a file that has been modified later than  the\n"
 "              given  time  and date, or one that has been modified before that\n"
 "              time. The date expression can be all sorts of date strings or if\n"
