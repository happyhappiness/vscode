"              Largefile\n"
"                     This curl supports transfers of large files, files larger\n"
"                     than 2GB.\n"
"\n"
"              IDN    This curl supports IDN - international domain names.\n"
"\n"
"              SSPI   SSPI  is  supported. If you use NTLM and set a blank user\n"
, stdout);
 fputs(
"                     name, curl will authenticate with your current  user  and\n"
"                     password.\n"
"\n"
"       -w/--write-out <format>\n"
"              Defines what to display on stdout after a completed and success-\n"
"              ful operation. The format is a string  that  may  contain  plain\n"
"              text mixed with any number of variables. The string can be spec-\n"
"              ified as \"string\", to get read from a particular file you  spec-\n"
, stdout);
 fputs(
"              ify  it  \"@filename\"  and  to  tell curl to read the format from\n"
"              stdin you write \"@-\".\n"
"\n"
"              The variables present in the output format will  be  substituted\n"
"              by  the  value or text that curl thinks fit, as described below.\n"
"              All variables are specified as %{variable_name} and to output  a\n"
"              normal  % you just write them as %%. You can output a newline by\n"
, stdout);
 fputs(
"              using \\n, a carriage return with \\r and a tab space with \\t.\n"
"\n"
"              NOTE: The %-symbol is a special symbol in the win32-environment,\n"
"              where  all  occurrences  of  %  must  be doubled when using this\n"
"              option.\n"
"\n"
"              The variables available at this point are:\n"
"\n"
"              url_effective  The URL that was fetched last. This is most mean-\n"
"                             ingful  if  you've  told curl to follow location:\n"
, stdout);
 fputs(
"                             headers.\n"
"\n"
"              http_code      The numerical response code that was found in the\n"
"                             last  retrieved  HTTP(S)  or  FTP(s) transfer. In\n"
"                             7.18.2 the alias response_code was added to  show\n"
"                             the same info.\n"
"\n"
"              http_connect   The  numerical  code  that  was found in the last\n"
"                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
, stdout);
 fputs(
"                             request. (Added in 7.12.4)\n"
"\n"
"              time_total     The  total time, in seconds, that the full opera-\n"
"                             tion lasted. The time will be displayed with mil-\n"
"                             lisecond resolution.\n"
"\n"
"              time_namelookup\n"
"                             The  time,  in  seconds,  it  took from the start\n"
"                             until the name resolving was completed.\n"
"\n"
, stdout);
 fputs(
"              time_connect   The time, in seconds,  it  took  from  the  start\n"
"                             until  the  TCP  connect  to  the remote host (or\n"
"                             proxy) was completed.\n"
"\n"
"              time_appconnect\n"
"                             The time, in seconds,  it  took  from  the  start\n"
"                             until  the  SSL/SSH/etc  connect/handshake to the\n"
"                             remote host was completed. (Added in 7.19.0)\n"
"\n"
, stdout);
 fputs(
"              time_pretransfer\n"
"                             The time, in seconds,  it  took  from  the  start\n"
"                             until  the file transfer was just about to begin.\n"
"                             This includes all pre-transfer commands and nego-\n"
"                             tiations that are specific to the particular pro-\n"
"                             tocol(s) involved.\n"
"\n"
"              time_redirect  The time, in seconds, it took for all redirection\n"
, stdout);
 fputs(
"                             steps  include  name lookup, connect, pretransfer\n"
"                             and transfer before  the  final  transaction  was\n"
"                             started.  time_redirect shows the complete execu-\n"
"                             tion time for multiple  redirections.  (Added  in\n"
"                             7.12.3)\n"
"\n"
"              time_starttransfer\n"
"                             The  time,  in  seconds,  it  took from the start\n"
, stdout);
 fputs(
"                             until the first byte was just about to be  trans-\n"
"                             ferred.  This  includes time_pretransfer and also\n"
"                             the time  the  server  needed  to  calculate  the\n"
"                             result.\n"
"\n"
"              size_download  The total amount of bytes that were downloaded.\n"
"\n"
"              size_upload    The total amount of bytes that were uploaded.\n"
"\n"
, stdout);
 fputs(
"              size_header    The total amount of bytes of the downloaded head-\n"
"                             ers.\n"
"\n"
"              size_request   The total amount of bytes that were sent  in  the\n"
"                             HTTP request.\n"
"\n"
"              speed_download The average download speed that curl measured for\n"
"                             the complete download.\n"
"\n"
"              speed_upload   The average upload speed that curl  measured  for\n"
"                             the complete upload.\n"
"\n"
, stdout);
 fputs(
"              content_type   The  Content-Type  of  the requested document, if\n"
"                             there was any.\n"
"\n"
"              num_connects   Number of new connects made in the recent  trans-\n"
"                             fer. (Added in 7.12.3)\n"
"\n"
"              num_redirects  Number  of  redirects  that  were followed in the\n"
"                             request. (Added in 7.12.3)\n"
"\n"
"              redirect_url   When a HTTP request was made without -L to follow\n"
, stdout);
 fputs(
"                             redirects, this variable will show the actual URL\n"
"                             a redirect would take you to. (Added in 7.18.2)\n"
"\n"
"              ftp_entry_path The initial path libcurl ended up in when logging\n"
"                             on to the remote FTP server. (Added in 7.15.4)\n"
"\n"
"              ssl_verify_result\n"
"                             The  result of the SSL peer certificate verifica-\n"
, stdout);
 fputs(
"                             tion that was requested. 0 means the verification\n"
"                             was successful. (Added in 7.19.0)\n"
"\n"
"       If this option is used several times, the last one will be used.\n"
"\n"
"       -x/--proxy <proxyhost[:port]>\n"
"              Use  the  specified HTTP proxy. If the port number is not speci-\n"
"              fied, it is assumed at port 1080.\n"
"\n"
"              This option overrides existing environment  variables  that  set\n"
, stdout);
 fputs(
"              the  proxy  to use. If there's an environment variable setting a\n"
"              proxy, you can set proxy to \"\" to override it.\n"
"\n"
"              Note that all operations that are performed over  a  HTTP  proxy\n"
"              will  transparently  be converted to HTTP. It means that certain\n"
"              protocol specific operations might not be available. This is not\n"
"              the  case  if you can tunnel through the proxy, as done with the\n"
"              -p/--proxytunnel option.\n"
"\n"
, stdout);
 fputs(
"              Starting with 7.14.1, the proxy host can be specified the  exact\n"
"              same  way as the proxy environment variables, including the pro-\n"
"              tocol prefix (http://) and the embedded user + password.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -X/--request <command>\n"
"              (HTTP) Specifies a custom request method to use when communicat-\n"
"              ing  with  the  HTTP server.  The specified request will be used\n"
, stdout);
 fputs(
"              instead of the method otherwise used (which  defaults  to  GET).\n"
"              Read  the  HTTP  1.1 specification for details and explanations.\n"
"              Common additional HTTP requests  include  PUT  and  DELETE,  but\n"
"              related technologies like WebDAV offers PROPFIND, COPY, MOVE and\n"
"              more.\n"
"\n"
"              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
"              doing file lists with FTP.\n"
"\n"
