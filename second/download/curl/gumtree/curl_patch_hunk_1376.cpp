 "          disable mute.\n"
 "\n"
 "     -S/--show-error\n"
 "          When used with -s it makes curl show error  message  if\n"
 "          it fails.\n"
 "\n"
-);
- puts(
 "          If  this  option  is  used twice, the second will again\n"
 "          disable show error.\n"
 "\n"
+);
+ puts(
 "     -t/--telnet-option <OPT=val>\n"
 "          Pass options to the telnet protocol. Supported  options\n"
 "          are:\n"
 "\n"
 "          TTYPE=<term> Sets the terminal type.\n"
 "\n"
 "          XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
 "          NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
 "     -T/--upload-file <file>\n"
 "          Like  -t,  but this transfers the specified local file.\n"
+"          If there is no file part in  the  specified  URL,  Curl\n"
 );
  puts(
-"          If there is no file part in  the  specified  URL,  Curl\n"
 "          will append the local file name. NOTE that you must use\n"
 "          a trailing / on the last directory to really  prove  to\n"
 "          Curl that there is no file name or curl will think that\n"
 "          your last directory name is the  remote  file  name  to\n"
 "          use.  That  will most likely cause the upload operation\n"
 "          to fail. If this is used on a http(s) server,  the  PUT\n"
 "          command will be used.\n"
 "\n"
+"          If this option is used several times, the last one will\n"
 );
  puts(
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+"          be used.\n"
 "\n"
 "     -u/--user <user:password>\n"
 "          Specify user and password to  use  when  fetching.  See\n"
 "          README.curl  for  detailed examples of how to use this.\n"
 "          If no password is  specified,  curl  will  ask  for  it\n"
 "          interactively.\n"
 "\n"
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -U/--proxy-user <user:password>\n"
+"          Specify user and password to use for Proxy  authentica�\n"
 );
  puts(
-"          Specify user and password to use for Proxy  authentica�\n"
 "          tion. If no password is specified, curl will ask for it\n"
 "          interactively.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     --url <URL>\n"
 "          Specify  a  URL  to  fetch. This option is mostly handy\n"
 "          when you wanna specify URL(s) in a config file.\n"
 "\n"
 "          This option may be used any number of times. To control\n"
-);
- puts(
 "          where  this  URL  is  written,  use  the  -o  or the -O\n"
 "          options.\n"
 "\n"
 "     -v/--verbose\n"
+);
+ puts(
 "          Makes  the  fetching  more  verbose/talkative.   Mostly\n"
 "          usable  for  debugging.  Lines  starting with '>' means\n"
 "          data sent by curl, '<' means data received by curl that\n"
 "          is  hidden  in normal cases and lines starting with '*'\n"
 "          means additional info provided by curl.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
-);
- puts(
 "          disable verbose.\n"
 "\n"
 "     -V/--version\n"
 "          Displays  the  full  version of curl, libcurl and other\n"
+);
+ puts(
 "          3rd party libraries linked with the executable.\n"
 "\n"
 "     -w/--write-out <format>\n"
 "          Defines what to display after a completed and  success�\n"
 "          ful  operation. The format is a string that may contain\n"
 "          plain text mixed with  any  number  of  variables.  The\n"
 "          string can be specified as \"string\", to get read from a\n"
-);
- puts(
 "          particular file you specify it \"@filename\" and to  tell\n"
 "          curl to read the format from stdin you write \"@-\".\n"
 "\n"
+);
+ puts(
 "          The variables present in the output format will be sub�\n"
 "          stituted by the value or text that curl thinks fit,  as\n"
 "          described  below.  All  variables  are  specified  like\n"
 "          %{variable_name} and to output  a  normal  %  you  just\n"
 "          write  them  like %%. You can output a newline by using\n"
-);
- puts(
 "          \\n, a carrige return with \\r and a tab space with \\t.\n"
 "\n"
 "          NOTE:  The  %-letter  is  a  special  letter   in   the\n"
+);
+ puts(
 "          win32-environment,  where  all occurrences of % must be\n"
 "          doubled when using this option.\n"
 "\n"
 "          Available variables are at this point:\n"
 "\n"
 "          url_effective  The URL that was fetched last.  This  is\n"
 "                         mostly meaningful if you've told curl to\n"
 "                         follow location: headers.\n"
 "\n"
-);
- puts(
 "          http_code      The numerical code that was found in the\n"
 "                         last retrieved HTTP(S) page.\n"
 "\n"
+);
+ puts(
 "          time_total     The  total  time,  in  seconds, that the\n"
 "                         full operation lasted. The time will  be\n"
 "                         displayed with millisecond resolution.\n"
 "\n"
 "          time_namelookup\n"
 "                         The  time,  in seconds, it took from the\n"
 "                         start until the name resolving was  com�\n"
-);
- puts(
 "                         pleted.\n"
 "\n"
 "          time_connect   The  time,  in seconds, it took from the\n"
+);
+ puts(
 "                         start until the connect  to  the  remote\n"
 "                         host (or proxy) was completed.\n"
 "\n"
 "          time_pretransfer\n"
 "                         The  time,  in seconds, it took from the\n"
 "                         start until the file  transfer  is  just\n"
 "                         about  to  begin. This includes all pre-\n"
-);
- puts(
 "                         transfer commands and negotiations  that\n"
 "                         are  specific  to  the particular proto�\n"
+);
+ puts(
 "                         col(s) involved.\n"
 "\n"
 "          size_download  The total  amount  of  bytes  that  were\n"
 "                         downloaded.\n"
 "\n"
 "          size_upload    The  total  amount  of  bytes  that were\n"
 "                         uploaded.\n"
 "\n"
 "          size_header    The total amount of bytes of  the  down�\n"
 "                         loaded headers.\n"
 "\n"
-);
- puts(
 "          size_request   The total amount of bytes that were sent\n"
 "                         in the HTTP request.\n"
 "\n"
+);
+ puts(
 "          speed_download The average  download  speed  that  curl\n"
 "                         measured for the complete download.\n"
 "          speed_upload   The  average upload speed that curl mea�\n"
 "                         sured for the complete upload.\n"
 "\n"
-"     If this option is used serveral times, the last one will  be\n"
+"     If this option is used several times, the last one  will  be\n"
 "     used.\n"
 "\n"
 "     -x/--proxy <proxyhost[:port]>\n"
-);
- puts(
 "          Use  specified  proxy. If the port number is not speci�\n"
 "          fied, it is assumed at port 1080.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+);
+ puts(
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -X/--request <command>\n"
 "          (HTTP)  Specifies a custom request to use when communi�\n"
 "          cating with the HTTP  server.   The  specified  request\n"
 "          will be used instead of the standard GET. Read the HTTP\n"
 "          1.1 specification for details and explanations.\n"
 "\n"
-);
- puts(
 "          (FTP) Specifies a custom FTP command to use instead  of\n"
 "          LIST when doing file lists with ftp.\n"
 "\n"
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+);
+ puts(
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -y/--speed-time <time>\n"
 "          If a download is slower than speed-limit bytes per sec�\n"
 "          ond  during  a  speed-time  period,  the  download gets\n"
 "          aborted. If speed-time is used, the default speed-limit\n"
 "          will be 1 unless set with -y.\n"
 "\n"
-);
- puts(
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -Y/--speed-limit <speed>\n"
+);
+ puts(
 "          If a download is slower than this given speed, in bytes\n"
 "          per  second,  for  speed-time  seconds it gets aborted.\n"
 "          speed-time is set with -Y and is 30 if not set.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -z/--time-cond <date expression>\n"
-);
- puts(
 "          (HTTP)  Request  to  get  a file that has been modified\n"
 "          later than the given time and date,  or  one  that  has\n"
+);
+ puts(
 "          been modified before that time. The date expression can\n"
 "          be all sorts of date strings or if it doesn't match any\n"
 "          internal  ones,  it  tries to get the time from a given\n"
 "          file name instead! See the  GNU  date(1)  or  curl_get�\n"
 "          date(3) man pages for date expression details.\n"
 "\n"
-);
- puts(
 "          Start  the  date  expression with a dash (-) to make it\n"
 "          request for a document that is  older  than  the  given\n"
+);
+ puts(
 "          date/time, default is a document that is newer than the\n"
 "          specified date/time.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -3/--sslv3\n"
 "          (HTTPS) Forces curl to use SSL version 3 when negotiat�\n"
 "          ing with a remote SSL server.\n"
 "\n"
 "     -2/--sslv2\n"
-);
- puts(
 "          (HTTPS) Forces curl to use SSL version 2 when negotiat�\n"
 "          ing with a remote SSL server.\n"
 "\n"
 "     -#/--progress-bar\n"
+);
+ puts(
 "          Make  curl  display  progress information as a progress\n"
 "          bar instead of the default statistics.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable the progress bar.\n"
 "\n"
 "     --crlf\n"
 "          (FTP)  Convert  LF  to  CRLF  in upload. Useful for MVS\n"
 "          (OS/390).\n"
 "\n"
-);
- puts(
 "          If this option is used twice,  the  second  will  again\n"
 "          disable crlf converting.\n"
 "\n"
 "     --stderr <file>\n"
+);
+ puts(
 "          Redirect  all  writes  to  stderr to the specified file\n"
 "          instead. If the file name is a plain '-', it is instead\n"
 "          written to stdout. This option has no point when you're\n"
 "          using a shell with decent redirecting capabilities.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "FILES\n"
 "     ~/.curlrc\n"
-);
- puts(
 "          Default config file.\n"
 "\n"
 "ENVIRONMENT\n"
 "     HTTP_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for HTTP.\n"
+);
+ puts(
 "\n"
 "     HTTPS_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for HTTPS.\n"
 "\n"
 "     FTP_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for FTP.\n"
 "     GOPHER_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for GOPHER.\n"
 "\n"
 "     ALL_PROXY [protocol://]<host>[:port]\n"
-);
- puts(
 "          Sets  proxy server to use if no protocol-specific proxy\n"
 "          is set.\n"
 "\n"
 "     NO_PROXY <comma-separated list of hosts>\n"
+);
+ puts(
 "          list of host names that shouldn't go through any proxy.\n"
 "          If set to a asterisk '*' only, it matches all hosts.\n"
 "\n"
 "     COLUMNS <integer>\n"
 "          The  width of the terminal.  This variable only affects\n"
 "          curl when the --progress-bar option is used.\n"
 "\n"
 "EXIT CODES\n"
 "     There exists a bunch of different error codes and their cor�\n"
-);
- puts(
 "     responding  error messages that may appear during bad condi�\n"
 "     tions. At the time of this writing, the exit codes are:\n"
 "\n"
+);
+ puts(
 "     1    Unsupported protocol. This build of curl has no support\n"
 "          for this protocol.\n"
 "\n"
 "     2    Failed to initialize.\n"
 "\n"
 "     3    URL malformat. The syntax was not correct.\n"
