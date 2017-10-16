 "\n"
 "       -R/--remote-time\n"
 "              When  used,  this  will  make  libcurl attempt to figure out the\n"
 "              timestamp of the remote file, and if that is available make  the\n"
 "              local file get that same timestamp.\n"
 "\n"
-"       --retry <num>\n"
-"              If  a  transient  error is returned when curl tries to perform a\n"
+"       --resolve <host:port:address>\n"
+"              Provide  a  custom  address  for  a specific host and port pair.\n"
+, stdout);
+ fputs(
+"              Using this, you can make the curl requests(s)  use  a  specified\n"
+"              address  and  prevent the otherwise normally resolved address to\n"
+"              be used. Consider it a sort of /etc/hosts  alternative  provided\n"
+"              on  the  command line. The port number should be the number used\n"
+"              for the specific protocol the host will be used  for.  It  means\n"
+"              you  need several entries if you want to provide address for the\n"
 , stdout);
  fputs(
+"              same host but different ports.\n"
+"\n"
+"              This option can be used many times to add  many  host  names  to\n"
+"              resolve.\n"
+"\n"
+"              (Added in 7.21.3)\n"
+"\n"
+"       --retry <num>\n"
+"              If  a  transient  error is returned when curl tries to perform a\n"
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
 "              If  this  option  is  used  multiple  times, the last occurrence\n"
 "              decide the amount.\n"
 "\n"
 "       --retry-delay <seconds>\n"
-, stdout);
- fputs(
 "              Make curl sleep this amount of time before  each  retry  when  a\n"
 "              transfer  has  failed  with  a  transient  error (it changes the\n"
+, stdout);
+ fputs(
 "              default backoff time algorithm between retries). This option  is\n"
 "              only  interesting if --retry is also used. Setting this delay to\n"
 "              zero will make curl use the default  backoff  time.   (Added  in\n"
 "              7.12.3)\n"
 "\n"
 "              If  this  option  is  used  multiple  times, the last occurrence\n"
-, stdout);
- fputs(
 "              determines the amount.\n"
 "\n"
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
 "              single  request's  maximum  time,  use  -m/--max-time.  Set this\n"
 "              option to zero to not timeout retries. (Added in 7.12.3)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is  used  multiple  times,  the  last  occurrence\n"
 "              determines the amount.\n"
 "\n"
 "       -s/--silent\n"
 "              Silent  or  quiet  mode. Don't show progress meter or error mes-\n"
 "              sages.  Makes Curl mute.\n"
 "\n"
 "       -S/--show-error\n"
-, stdout);
- fputs(
 "              When used with -s it makes curl show  an  error  message  if  it\n"
 "              fails.\n"
 "\n"
 "       --socks4 <host[:port]>\n"
 "              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
+, stdout);
+ fputs(
 "              fied, it is assumed at port 1080. (Added in 7.15.2)\n"
 "\n"
 "              This option overrides any previous use of  -x/--proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       --socks4a <host[:port]>\n"
 "              Use the specified SOCKS4a proxy. If the port number is not spec-\n"
 "              ified, it is assumed at port 1080. (Added in 7.18.0)\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides any previous use of  -x/--proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks5-hostname <host[:port]>\n"
 "              Use  the  specified  SOCKS5 proxy (and let the proxy resolve the\n"
-, stdout);
- fputs(
 "              host name). If the port number is not specified, it  is  assumed\n"
 "              at port 1080. (Added in 7.18.0)\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  overrides  any previous use of -x/--proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This  option  was  previously  wrongly  documented  and used as\n"
 "              --socks without the number appended.)\n"
 "\n"
 "       --socks5 <host[:port]>\n"
+"              Use the specified SOCKS5 proxy  -  but  resolve  the  host  name\n"
 , stdout);
  fputs(
-"              Use the specified SOCKS5 proxy  -  but  resolve  the  host  name\n"
 "              locally.  If  the port number is not specified, it is assumed at\n"
 "              port 1080.\n"
 "\n"
 "              This option overrides any previous use of  -x/--proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This option was  previously  wrongly  documented  and  used  as\n"
-, stdout);
- fputs(
 "              --socks without the number appended.)\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option (as well as --socks4) does not work with IPV6, FTPS\n"
 "              or LDAP.\n"
 "\n"
 "       --socks5-gssapi-service <servicename>\n"
 "              The default service name for a socks server is rcmd/server-fqdn.\n"
 "              This option allows you to change it.\n"
 "\n"
 "              Examples:\n"
 "               --socks5  proxy-name  --socks5-gssapi-service sockd   would use\n"
 "              sockd/proxy-name\n"
+"               --socks5  proxy-name  --socks5-gssapi-service   sockd/real-name\n"
 , stdout);
  fputs(
-"               --socks5  proxy-name  --socks5-gssapi-service   sockd/real-name\n"
 "              would  use  sockd/real-name  for cases where the proxy-name does\n"
 "              not match the princpal name.\n"
 "               (Added in 7.19.4).\n"
 "\n"
 "       --socks5-gssapi-nec\n"
 "              As part of the gssapi negotiation a protection mode  is  negoti-\n"
 "              ated.  The  rfc1961  says  in  section 4.3/4.4 it should be pro-\n"
 "              tected, but the NEC  reference  implementation  does  not.   The\n"
+"              option  --socks5-gssapi-nec  allows  the unprotected exchange of\n"
 , stdout);
  fputs(
-"              option  --socks5-gssapi-nec  allows  the unprotected exchange of\n"
 "              the protection mode negotiation. (Added in 7.19.4).\n"
 "\n"
 "       --stderr <file>\n"
 "              Redirect all writes to stderr to the specified file instead.  If\n"
 "              the  file  name is a plain '-', it is instead written to stdout.\n"
 "              This option has no point when you're using a shell  with  decent\n"
 "              redirecting capabilities.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --tcp-nodelay\n"
+, stdout);
+ fputs(
 "              Turn  on the TCP_NODELAY option. See the curl_easy_setopt(3) man\n"
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
 "       -t/--telnet-option <OPT=val>\n"
 "              Pass options to the telnet protocol. Supported options are:\n"
 "\n"
 "              TTYPE=<term> Sets the terminal type.\n"
 "\n"
 "              XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
-, stdout);
- fputs(
 "              NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
 "       --tftp-blksize <value>\n"
+, stdout);
+ fputs(
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
 "              size  that curl will try to use when tranferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "       -T/--upload-file <file>\n"
+"              This transfers the specified local file to the  remote  URL.  If\n"
 , stdout);
  fputs(
-"              This transfers the specified local file to the  remote  URL.  If\n"
 "              there is no file part in the specified URL, Curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory  to really prove to Curl that there is no file name or\n"
 "              curl will think that your last directory name is the remote file\n"
 "              name to use. That will most likely cause the upload operation to\n"
-, stdout);
- fputs(
 "              fail. If this is used on a HTTP(S) server, the PUT command  will\n"
 "              be used.\n"
 "\n"
+, stdout);
+ fputs(
 "              Use  the file name \"-\" (a single dash) to use stdin instead of a\n"
 "              given file.  Alternately, the file name \".\"  (a  single  period)\n"
 "              may  be  specified  instead  of \"-\" to use stdin in non-blocking\n"
 "              mode to  allow  reading  server  output  while  stdin  is  being\n"
 "              uploaded.\n"
 "\n"
+"              You can specify one -T for each URL on the command line. Each -T\n"
 , stdout);
  fputs(
-"              You can specify one -T for each URL on the command line. Each -T\n"
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
 "       --trace <file>\n"
+, stdout);
+ fputs(
 "              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
 "              This  option overrides previous uses of -v/--verbose or --trace-\n"
 "              ascii.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
+, stdout);
+ fputs(
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
 "              This is very similar to --trace, but leaves out the hex part and\n"
 "              only  shows  the ASCII part of the dump. It makes smaller output\n"
-, stdout);
- fputs(
 "              that might be easier to read for untrained humans.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides previous uses of -v/--verbose or --trace.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "       -u/--user <user:password>\n"
 "              Specify the user name and password to use for server authentica-\n"
-, stdout);
- fputs(
 "              tion. Overrides -n/--netrc and --netrc-optional.\n"
 "\n"
+, stdout);
+ fputs(
 "              If you just give the user name (without entering a  colon)  curl\n"
 "              will prompt for a password.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-u :\".\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "       -U/--proxy-user <user:password>\n"
 "              Specify the user name and password to use for proxy  authentica-\n"
 "              tion.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-U :\".\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "       --url <URL>\n"
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
 "              This  option  may  be used any number of times. To control where\n"
 "              this URL is written, use the -o/--output or the -O/--remote-name\n"
 "              options.\n"
 "\n"
 "       -v/--verbose\n"
+"              Makes  the  fetching  more  verbose/talkative. Mostly useful for\n"
 , stdout);
  fputs(
-"              Makes  the  fetching  more  verbose/talkative. Mostly useful for\n"
 "              debugging. A line starting with '>' means \"header data\" sent  by\n"
 "              curl, '<' means \"header data\" received by curl that is hidden in\n"
 "              normal cases, and a line starting with '*' means additional info\n"
 "              provided by curl.\n"
 "\n"
 "              Note  that  if  you  only  want  HTTP  headers  in  the  output,\n"
 "              -i/--include might be the option you're looking for.\n"
 "\n"
+"              If you think this option still doesn't give you enough  details,\n"
 , stdout);
  fputs(
-"              If you think this option still doesn't give you enough  details,\n"
 "              consider using --trace or --trace-ascii instead.\n"
 "\n"
 "              This option overrides previous uses of --trace-ascii or --trace.\n"
 "\n"
 "              Use -S/--silent to make curl quiet.\n"
 "\n"
 "       -V/--version\n"
 "              Displays information about curl and the libcurl version it uses.\n"
 "              The  first  line  includes the full version of curl, libcurl and\n"
-, stdout);
- fputs(
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
+, stdout);
+ fputs(
 "              The second line (starts with \"Protocols:\") shows  all  protocols\n"
 "              that libcurl reports to support.\n"
 "\n"
 "              The third line (starts with \"Features:\") shows specific features\n"
 "              libcurl reports to offer. Available features include:\n"
 "\n"
