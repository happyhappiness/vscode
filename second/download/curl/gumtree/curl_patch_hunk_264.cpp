 "              authentication but may be also used along with another authenti‐\n"
 , stdout);
  fputs(
 "              cation methods. For  more  information  see  IETF  draft  draft-\n"
 "              brezak-spnego-http-04.txt.\n"
 "\n"
+"              If  you  want to enable Negotiate for your proxy authentication,\n"
+"              then use --proxy-negotiate.\n"
+"\n"
 "              This option requires that the library was built with GSSAPI sup‐\n"
-"              port. This is not very common. Use -V/--version to see  if  your\n"
+"              port.  This  is not very common. Use -V/--version to see if your\n"
 "              version supports GSS-Negotiate.\n"
 "\n"
-"              When  using  this option, you must also provide a fake -u/--user\n"
-"              option to activate the authentication code properly.  Sending  a\n"
 , stdout);
  fputs(
-"              ’-u  :’  is  enough  as  the  user name and password from the -u\n"
+"              When using this option, you must also provide a  fake  -u/--user\n"
+"              option  to  activate the authentication code properly. Sending a\n"
+"              ’-u :’ is enough as the user  name  and  password  from  the  -u\n"
 "              option aren’t actually used.\n"
 "\n"
-"              If this option is used several times, the following  occurrences\n"
+"              If  this option is used several times, the following occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -N/--no-buffer\n"
-"              Disables the buffering of the output stream. In normal work sit‐\n"
-"              uations, curl will use a standard buffered  output  stream  that\n"
 , stdout);
  fputs(
+"              Disables the buffering of the output stream. In normal work sit‐\n"
+"              uations,  curl  will  use a standard buffered output stream that\n"
 "              will have the effect that it will output the data in chunks, not\n"
-"              necessarily exactly when the data arrives.   Using  this  option\n"
+"              necessarily  exactly  when  the data arrives.  Using this option\n"
 "              will disable that buffering.\n"
 "\n"
-"              If  this  option  is used twice, the second will again switch on\n"
+"              If this option is used twice, the second will  again  switch  on\n"
 "              buffering.\n"
 "\n"
 "       --no-sessionid\n"
-"              (SSL) Disable curl’s use of SSL session-ID caching.  By  default\n"
-"              all  transfers are done using the cache. Note that while nothing\n"
 , stdout);
  fputs(
-"              ever should get hurt by attempting  to  reuse  SSL  session-IDs,\n"
+"              (SSL)  Disable curl’s use of SSL session-ID caching.  By default\n"
+"              all transfers are done using the cache. Note that while  nothing\n"
+"              ever  should  get  hurt  by attempting to reuse SSL session-IDs,\n"
 "              there seem to be broken SSL implementations in the wild that may\n"
-"              require you to disable this in order for you to succeed.  (Added\n"
+"              require  you to disable this in order for you to succeed. (Added\n"
 "              in 7.16.0)\n"
 "\n"
-"              If  this  option  is used twice, the second will again switch on\n"
-"              use of the session cache.\n"
-"\n"
-"       --ntlm (HTTP) Enables  NTLM  authentication.  The  NTLM  authentication\n"
 , stdout);
  fputs(
+"              If this option is used twice, the second will  again  switch  on\n"
+"              use of the session cache.\n"
+"\n"
+"       --ntlm (HTTP)  Enables  NTLM  authentication.  The  NTLM authentication\n"
 "              method was designed by Microsoft and is used by IIS web servers.\n"
 "              It is a proprietary protocol, reversed engineered by clever peo‐\n"
 "              ple and implemented in curl based on their efforts. This kind of\n"
-"              behavior should not be endorsed, you should  encourage  everyone\n"
-"              who  uses  NTLM to switch to a public and documented authentica‐\n"
-"              tion method instead. Such as Digest.\n"
-"\n"
 , stdout);
  fputs(
-"              If you want to enable NTLM for your proxy  authentication,  then\n"
+"              behavior  should  not be endorsed, you should encourage everyone\n"
+"              who uses NTLM to switch to a public and  documented  authentica‐\n"
+"              tion method instead. Such as Digest.\n"
+"\n"
+"              If  you  want to enable NTLM for your proxy authentication, then\n"
 "              use --proxy-ntlm.\n"
 "\n"
-"              This  option  requires  that the library was built with SSL sup‐\n"
+"              This option requires that the library was built  with  SSL  sup‐\n"
 "              port. Use -V/--version to see if your curl supports NTLM.\n"
 "\n"
-"              If this option is used several times, the following  occurrences\n"
+, stdout);
+ fputs(
+"              If  this option is used several times, the following occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -o/--output <file>\n"
 "              Write output to <file> instead of stdout. If you are using {} or\n"
-, stdout);
- fputs(
-"              [] to fetch multiple documents, you can use ’#’  followed  by  a\n"
-"              number  in  the <file> specifier. That variable will be replaced\n"
+"              []  to  fetch  multiple documents, you can use ’#’ followed by a\n"
+"              number in the <file> specifier. That variable will  be  replaced\n"
 "              with the current string for the URL being fetched. Like in:\n"
 "\n"
+, stdout);
+ fputs(
 "                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
 "              or use several variables like:\n"
 "\n"
 "                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
 "\n"
-"              You may use this option as many times  as  you  have  number  of\n"
-, stdout);
- fputs(
+"              You  may  use  this  option  as many times as you have number of\n"
 "              URLs.\n"
 "\n"
-"              See  also  the --create-dirs option to create the local directo‐\n"
+"              See also the --create-dirs option to create the  local  directo‐\n"
 "              ries dynamically.\n"
 "\n"
 "       -O/--remote-name\n"
-"              Write output to a local file named like the remote file we  get.\n"
-"              (Only  the file part of the remote file is used, the path is cut\n"
+"              Write  output to a local file named like the remote file we get.\n"
+, stdout);
+ fputs(
+"              (Only the file part of the remote file is used, the path is  cut\n"
 "              off.)\n"
 "\n"
-"              The remote file name to use for saving  is  extracted  from  the\n"
+"              The  remote  file  name  to use for saving is extracted from the\n"
 "              given URL, nothing else.\n"
 "\n"
-, stdout);
- fputs(
-"              You  may  use  this  option  as many times as you have number of\n"
+"              You may use this option as many times  as  you  have  number  of\n"
 "              URLs.\n"
 "\n"
 "       --pass <phrase>\n"
 "              (SSL/SSH) Pass phrase for the private key\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-"       --proxy-anyauth\n"
-"              Tells  curl to pick a suitable authentication method when commu‐\n"
-"              nicating  with  the  given  proxy.  This  will  cause  an  extra\n"
+"       --post301\n"
+, stdout);
+ fputs(
+"              Tells curl to respect  RFC  2616/10.3.2  and  not  convert  POST\n"
+"              requests into GET requests when following a 301 redirection. The\n"
+"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
+"              the  conversion  by  default to maintain consistency. However, a\n"
+"              server may requires a POST to remain a POST after such  a  redi‐\n"
+"              rection. This option is meaningful only when using -L/--location\n"
 , stdout);
  fputs(
+"              (Added in 7.17.1)\n"
+"\n"
+"       --proxy-anyauth\n"
+"              Tells curl to pick a suitable authentication method when  commu‐\n"
+"              nicating  with  the  given  proxy.  This  will  cause  an  extra\n"
 "              request/response round-trip. (Added in 7.13.2)\n"
 "\n"
-"              If  this option is used twice, the second will again disable the\n"
+"              If this option is used twice, the second will again disable  the\n"
 "              proxy use-any authentication.\n"
 "\n"
 "       --proxy-basic\n"
-"              Tells curl to use HTTP Basic authentication  when  communicating\n"
+, stdout);
+ fputs(
+"              Tells  curl  to use HTTP Basic authentication when communicating\n"
 "              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
-"              remote host. Basic is the  default  authentication  method  curl\n"
+"              remote  host.  Basic  is  the default authentication method curl\n"
 "              uses with proxies.\n"
 "\n"
-, stdout);
- fputs(
-"              If  this  option  is  used  twice, the second will again disable\n"
+"              If this option is used twice,  the  second  will  again  disable\n"
 "              proxy HTTP Basic authentication.\n"
 "\n"
 "       --proxy-digest\n"
-"              Tells curl to use HTTP Digest authentication when  communicating\n"
+"              Tells  curl to use HTTP Digest authentication when communicating\n"
+, stdout);
+ fputs(
 "              with the given proxy. Use --digest for enabling HTTP Digest with\n"
 "              a remote host.\n"
 "\n"
-"              If this option is used twice,  the  second  will  again  disable\n"
+"              If  this  option  is  used  twice, the second will again disable\n"
 "              proxy HTTP Digest.\n"
 "\n"
-"       --proxy-ntlm\n"
+"       --proxy-negotiate\n"
+"              Tells curl to use HTTP Negotiate authentication when communicat‐\n"
+"              ing  with  the  given  proxy.  Use --negotiate for enabling HTTP\n"
+"              Negotiate with a remote host.\n"
+"\n"
 , stdout);
  fputs(
+"              If this option is used twice,  the  second  will  again  disable\n"
+"              proxy HTTP Negotiate. (Added in 7.17.1)\n"
+"\n"
+"       --proxy-ntlm\n"
 "              Tells  curl  to  use HTTP NTLM authentication when communicating\n"
 "              with the given proxy. Use --ntlm for enabling NTLM with a remote\n"
 "              host.\n"
 "\n"
 "              If  this  option  is  used  twice, the second will again disable\n"
 "              proxy HTTP NTLM.\n"
 "       -p/--proxytunnel\n"
-"              When an HTTP proxy is used (-x/--proxy), this option will  cause\n"
-"              non-HTTP  protocols  to  attempt  to  tunnel  through  the proxy\n"
 , stdout);
  fputs(
+"              When an HTTP proxy is used (-x/--proxy), this option will  cause\n"
+"              non-HTTP  protocols  to  attempt  to  tunnel  through  the proxy\n"
 "              instead of merely using it to do HTTP-like operations. The  tun‐\n"
 "              nel  approach  is  made  with the HTTP proxy CONNECT request and\n"
 "              requires that the proxy allows direct connect to the remote port\n"
 "              number curl wants to tunnel through to.\n"
 "\n"
+, stdout);
+ fputs(
 "              If  this  option  is  used  twice, the second will again disable\n"
 "              proxy tunnel.\n"
 "\n"
 "       --pubkey <key>\n"
-, stdout);
- fputs(
 "              (SSH) Public key file name. Allows you to  provide  your  public\n"
 "              key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -P/--ftp-port <address>\n"
 "              (FTP) Reverses the initiator/listener roles when connecting with\n"
-"              ftp.  This  switch  makes  Curl  use the PORT command instead of\n"
-"              PASV. In practise, PORT tells  the  server  to  connect  to  the\n"
 , stdout);
  fputs(
+"              ftp.  This  switch  makes  Curl  use the PORT command instead of\n"
+"              PASV. In practise, PORT tells  the  server  to  connect  to  the\n"
 "              client’s  specified address and port, while PASV asks the server\n"
 "              for an ip address and port to connect to.  <address>  should  be\n"
 "              one of:\n"
 "\n"
 "              interface\n"
 "                     i.e  \"eth0\"  to  specify which interface’s IP address you\n"
 "                     want to use  (Unix only)\n"
 "\n"
+, stdout);
+ fputs(
 "              IP address\n"
 "                     i.e \"192.168.10.1\" to specify exact IP number\n"
 "\n"
 "              host name\n"
-, stdout);
- fputs(
 "                     i.e \"my.host.domain\" to specify machine\n"
 "\n"
 "              -      make curl pick the same IP address that is  already  used\n"
 "                     for the control connection\n"
 "\n"
 "       If  this  option is used several times, the last one will be used. Dis‐\n"
 "       able the use of PORT with --ftp-pasv. Disable the attempt  to  use  the\n"
+, stdout);
+ fputs(
 "       EPRT  command  instead  of PORT by using --disable-eprt. EPRT is really\n"
 "       PORT++.\n"
 "\n"
-, stdout);
- fputs(
 "       -q     If used as the first parameter on the command line,  the  curlrc\n"
 "              config  file  will not be read and used. See the -K/--config for\n"
 "              details on the default config file search path.\n"
 "\n"
 "       -Q/--quote <command>\n"
 "              (FTP/SFTP) Send an arbitrary command to the remote FTP  or  SFTP\n"
-"              server.  Quote  commands  are sent BEFORE the transfer is taking\n"
-"              place (just after the initial PWD command in an FTP transfer, to\n"
 , stdout);
  fputs(
+"              server.  Quote  commands  are sent BEFORE the transfer is taking\n"
+"              place (just after the initial PWD command in an FTP transfer, to\n"
 "              be exact). To make commands take place after a successful trans‐\n"
 "              fer, prefix them with a dash ’-’.  To  make  commands  get  sent\n"
 "              after  libcurl  has  changed  working directory, just before the\n"
 "              transfer command(s), prefix the command with ’+’ (this  is  only\n"
-"              supported  for  FTP). You may specify any number of commands. If\n"
-"              the server returns failure for one of the commands,  the  entire\n"
 , stdout);
  fputs(
+"              supported  for  FTP). You may specify any number of commands. If\n"
+"              the server returns failure for one of the commands,  the  entire\n"
 "              operation  will  be aborted. You must send syntactically correct\n"
 "              FTP commands as RFC959 defines to FTP servers,  or  one  of  the\n"
 "              following commands (with appropriate arguments) to SFTP servers:\n"
 "              chgrp, chmod, chown, ln, mkdir, pwd, rename, rm, rmdir, symlink.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option can be used multiple times.\n"
 "\n"
 "       --random-file <file>\n"
 "              (SSL) Specify the path name to file containing what will be con‐\n"
-, stdout);
- fputs(
 "              sidered as random data. The data is  used  to  seed  the  random\n"
 "              engine for SSL connections.  See also the --egd-file option.\n"
 "\n"
 "       -r/--range <range>\n"
 "              (HTTP/FTP) Retrieve a byte range (i.e a partial document) from a\n"
+, stdout);
+ fputs(
 "              HTTP/1.1 or FTP server. Ranges can be specified in a  number  of\n"
 "              ways.\n"
 "\n"
 "              0-499     specifies the first 500 bytes\n"
 "\n"
 "              500-999   specifies the second 500 bytes\n"
 "\n"
-, stdout);
- fputs(
 "              -500      specifies the last 500 bytes\n"
 "\n"
 "              9500-     specifies the bytes from offset 9500 and forward\n"
 "\n"
 "              0-0,-1    specifies the first and last byte only(*)(H)\n"
 "\n"
 "              500-700,600-799\n"
+, stdout);
+ fputs(
 "                        specifies 300 bytes from offset 500(H)\n"
 "\n"
 "              100-199,500-599\n"
 "                        specifies two separate 100 bytes ranges(*)(H)\n"
 "\n"
 "       (*)  =  NOTE  that this will cause the server to reply with a multipart\n"
 "       response!\n"
 "\n"
-, stdout);
- fputs(
 "       Only digit characters (0-9) are valid in ’start’ and  ’stop’  of  range\n"
 "       syntax  ’start-stop’.  If  a non-digit character is given in the range,\n"
+, stdout);
+ fputs(
 "       the server’s response will be indeterminable,  depending  on  different\n"
 "       server’s configuration.\n"
 "\n"
 "       You  should  also  be aware that many HTTP/1.1 servers do not have this\n"
 "       feature enabled, so that when  you  attempt  to  get  a  range,  you’ll\n"
 "       instead get the whole document.\n"
 "\n"
-, stdout);
- fputs(
 "       FTP  range  downloads  only  support  the  simple  syntax  ’start-stop’\n"
 "       (optionally with one of the numbers omitted). It depends on the non-RFC\n"
 "       command SIZE.\n"
 "\n"
+, stdout);
+ fputs(
 "       If this option is used several times, the last one will be used.\n"
 "\n"
 "       --raw  When  used, it disables all internal HTTP decoding of content or\n"
 "              transfer encodings and instead makes them passed  on  unaltered,\n"
 "              raw. (Added in 7.16.2)\n"
 "\n"
-, stdout);
- fputs(
 "              If  this  option  is used several times, each occurrence toggles\n"
 "              this on/off.\n"
 "\n"
 "       -R/--remote-time\n"
 "              When used, this will make libcurl  attempt  to  figure  out  the\n"
+, stdout);
+ fputs(
 "              timestamp  of the remote file, and if that is available make the\n"
 "              local file get that same timestamp.\n"
 "\n"
 "              If this option is used twice,  the  second  time  disables  this\n"
 "              again.\n"
 "\n"
 "       --retry <num>\n"
-, stdout);
- fputs(
 "              If  a  transient  error is returned when curl tries to perform a\n"
 "              transfer, it will retry this number of times before  giving  up.\n"
 "              Setting  the  number to 0 makes curl do no retries (which is the\n"
+, stdout);
+ fputs(
 "              default). Transient error means either: a timeout,  an  FTP  5xx\n"
 "              response code or an HTTP 5xx response code.\n"
 "\n"
 "              When  curl  is about to retry a transfer, it will first wait one\n"
-, stdout);
- fputs(
 "              second and then for all forthcoming retries it will  double  the\n"
 "              waiting  time until it reaches 10 minutes which then will be the\n"
 "              delay between the rest of the retries.  By  using  --retry-delay\n"
+, stdout);
+ fputs(
 "              you   disable  this  exponential  backoff  algorithm.  See  also\n"
 "              --retry-max-time to limit the total time  allowed  for  retries.\n"
 "              (Added in 7.12.3)\n"
 "\n"
-, stdout);
- fputs(
 "              If  this  option  is  used  multiple  times, the last occurrence\n"
 "              decide the amount.\n"
 "\n"
 "       --retry-delay <seconds>\n"
 "              Make curl sleep this amount of time between each  retry  when  a\n"
 "              transfer  has  failed  with  a  transient  error (it changes the\n"
-"              default backoff time algorithm between retries). This option  is\n"
-"              only  interesting if --retry is also used. Setting this delay to\n"
 , stdout);
  fputs(
+"              default backoff time algorithm between retries). This option  is\n"
+"              only  interesting if --retry is also used. Setting this delay to\n"
 "              zero will make curl use the default  backoff  time.   (Added  in\n"
 "              7.12.3)\n"
 "\n"
 "              If  this  option  is  used  multiple  times, the last occurrence\n"
 "              decide the amount.\n"
 "\n"
 "       --retry-max-time <seconds>\n"
 "              The retry timer is reset  before  the  first  transfer  attempt.\n"
-"              Retries will be done as usual (see --retry) as long as the timer\n"
-"              hasn’t reached this given limit. Notice that if the timer hasn’t\n"
 , stdout);
  fputs(
+"              Retries will be done as usual (see --retry) as long as the timer\n"
+"              hasn’t reached this given limit. Notice that if the timer hasn’t\n"
 "              reached  the  limit, the request will be made and while perform‐\n"
 "              ing, it may take longer than this given time period. To limit  a\n"
 "              single  request´s  maximum  time,  use  -m/--max-time.  Set this\n"
 "              option to zero to not timeout retries. (Added in 7.12.3)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is  used  multiple  times,  the  last  occurrence\n"
 "              decide the amount.\n"
 "\n"
 "       -s/--silent\n"
-, stdout);
- fputs(
 "              Silent mode. Don’t show progress meter or error messages.  Makes\n"
 "              Curl mute.\n"
 "\n"
 "              If this option is used twice,  the  second  will  again  disable\n"
 "              silent mode.\n"
 "\n"
 "       -S/--show-error\n"
 "              When  used with -s it makes curl show error message if it fails.\n"
+, stdout);
+ fputs(
 "              If this option is used twice, the second will again disable show\n"
 "              error.\n"
 "\n"
 "       --socks4 <host[:port]>\n"
-, stdout);
- fputs(
 "              Use the specified SOCKS4 proxy. If the port number is not speci‐\n"
 "              fied, it is assumed at port 1080. (Added in 7.15.2)\n"
 "\n"
 "              This option overrides any previous use of  -x/--proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-"       --socks5 <host[:port]>\n"
-"              Use the specified SOCKS5 proxy. If the port number is not speci‐\n"
 , stdout);
  fputs(
+"       --socks5 <host[:port]>\n"
+"              Use the specified SOCKS5 proxy. If the port number is not speci‐\n"
 "              fied, it is assumed at port 1080. (Added in 7.11.1)\n"
 "\n"
 "              This  option  overrides  any previous use of -x/--proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "              (This  option  was  previously  wrongly  documented  and used as\n"
+, stdout);
+ fputs(
 "              --socks without the number appended.)\n"
 "\n"
 "       --stderr <file>\n"
 "              Redirect all writes to stderr to the specified file instead.  If\n"
-, stdout);
- fputs(
 "              the  file  name is a plain ’-’, it is instead written to stdout.\n"
 "              This option has no point when you’re using a shell  with  decent\n"
 "              redirecting capabilities.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --tcp-nodelay\n"
+, stdout);
+ fputs(
 "              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
-, stdout);
- fputs(
 "              If  this  option  is used several times, each occurrence toggles\n"
 "              this on/off.\n"
 "\n"
 "       -t/--telnet-option <OPT=val>\n"
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
 "       -T/--upload-file <file>\n"
-, stdout);
- fputs(
 "              This transfers the specified local file to the  remote  URL.  If\n"
 "              there is no file part in the specified URL, Curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
 "              directory  to really prove to Curl that there is no file name or\n"
 "              curl will think that your last directory name is the remote file\n"
-"              name to use. That will most likely cause the upload operation to\n"
 , stdout);
  fputs(
+"              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on a http(s) server, the PUT command  will\n"
 "              be used.\n"
 "\n"
 "              Use  the file name \"-\" (a single dash) to use stdin instead of a\n"
 "              given file.\n"
 "\n"
 "              You can specify one -T for each URL on the command line. Each -T\n"
 "              + URL pair specifies what to upload and to where. curl also sup‐\n"
-"              ports \"globbing\" of the -T argument, meaning that you can upload\n"
 , stdout);
  fputs(
+"              ports \"globbing\" of the -T argument, meaning that you can upload\n"
 "              multiple  files  to  a single URL by using the same URL globbing\n"
 "              style supported in the URL, like this:\n"
 "\n"
 "              curl -T \"{file1,file2}\" http://www.uploadtothissite.com\n"
 "\n"
 "              or even\n"
 "\n"
 "              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
 "\n"
 "       --trace <file>\n"
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
-"              including descriptive information, to the given output file. Use\n"
 , stdout);
  fputs(
+"              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
 "              This option overrides previous uses of -v/--verbose or  --trace-\n"
 "              ascii.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
-"              including descriptive information, to the given output file. Use\n"
-"              \"-\" as filename to have the output sent to stdout.\n"
 , stdout);
  fputs(
+"              including descriptive information, to the given output file. Use\n"
+"              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
 "              This is very similar to --trace, but leaves out the hex part and\n"
 "              only  shows  the ASCII part of the dump. It makes smaller output\n"
 "              that might be easier to read for untrained humans.\n"
 "\n"
 "              This option overrides previous uses of -v/--verbose or  --trace.\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends a time stamp to each trace or verbose  line  that  curl\n"
-, stdout);
- fputs(
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "              If  this option is used several times, each occurrence will tog‐\n"
 "              gle it on/off.\n"
 "\n"
 "       -u/--user <user:password>\n"
 "              Specify user and password  to  use  for  server  authentication.\n"
+, stdout);
+ fputs(
 "              Overrides -n/--netrc and --netrc-optional.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica‐\n"
 "              tion, you can force curl to pick up the user name  and  password\n"
-, stdout);
- fputs(
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-u :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -U/--proxy-user <user:password>\n"
+, stdout);
+ fputs(
 "              Specify user and password to use for proxy authentication.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica‐\n"
 "              tion, you can force curl to pick up the user name  and  password\n"
-, stdout);
- fputs(
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-U :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --url <URL>\n"
+, stdout);
+ fputs(
 "              Specify  a  URL  to  fetch. This option is mostly handy when you\n"
 "              want to specify URL(s) in a config file.\n"
 "\n"
 "              This option may be used any number of times.  To  control  where\n"
-, stdout);
- fputs(
 "              this URL is written, use the -o/--output or the -O/--remote-name\n"
 "              options.\n"
 "\n"
 "       -v/--verbose\n"
 "              Makes the fetching more  verbose/talkative.  Mostly  usable  for\n"
 "              debugging.  Lines  starting with ’>’ means \"header data\" sent by\n"
+, stdout);
+ fputs(
 "              curl, ’<’ means \"header data\" received by curl that is hidden in\n"
 "              normal  cases  and lines starting with ’*’ means additional info\n"
 "              provided by curl.\n"
 "\n"
-, stdout);
- fputs(
 "              Note  that  if  you  only  want  HTTP  headers  in  the  output,\n"
 "              -i/--include might be option you’re looking for.\n"
 "\n"
 "              If  you think this option still doesn’t give you enough details,\n"
 "              consider using --trace or --trace-ascii instead.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides previous uses of --trace-ascii or --trace.\n"
 "              If  this option is used twice, the second will do nothing extra.\n"
 "\n"
 "       -V/--version\n"
-, stdout);
- fputs(
 "              Displays information about curl and the libcurl version it uses.\n"
 "              The  first  line  includes the full version of curl, libcurl and\n"
 "              other 3rd party libraries linked with the executable.\n"
 "\n"
 "              The second line (starts with \"Protocols:\") shows  all  protocols\n"
+, stdout);
+ fputs(
 "              that libcurl reports to support.\n"
 "\n"
 "              The third line (starts with \"Features:\") shows specific features\n"
-, stdout);
- fputs(
 "              libcurl reports to offer. Available features include:\n"
 "\n"
 "              IPv6   You can use IPv6 with this.\n"
 "\n"
 "              krb4   Krb4 for ftp is supported.\n"
 "\n"
 "              SSL    HTTPS and FTPS are supported.\n"
 "\n"
 "              libz   Automatic decompression of compressed files over HTTP  is\n"
 "                     supported.\n"
 "\n"
+, stdout);
+ fputs(
 "              NTLM   NTLM authentication is supported.\n"
 "\n"
 "              GSS-Negotiate\n"
 "                     Negotiate authentication and krb5 for ftp is supported.\n"
 "\n"
-, stdout);
- fputs(
 "              Debug  This  curl  uses a libcurl built with Debug. This enables\n"
 "                     more error-tracking and memory debugging etc.  For  curl-\n"
 "                     developers only!\n"
 "\n"
 "              AsynchDNS\n"
 "                     This curl uses asynchronous name resolves.\n"
 "\n"
+, stdout);
+ fputs(
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
 "                     name,  curl  will authenticate with your current user and\n"
 "                     password.\n"
 "\n"
 "       -w/--write-out <format>\n"
-"              Defines what to display on stdout after a completed and success‐\n"
-"              ful  operation.  The  format  is a string that may contain plain\n"
 , stdout);
  fputs(
+"              Defines what to display on stdout after a completed and success‐\n"
+"              ful  operation.  The  format  is a string that may contain plain\n"
 "              text mixed with any number of variables. The string can be spec‐\n"
 "              ified  as \"string\", to get read from a particular file you spec‐\n"
 "              ify it \"@filename\" and to tell curl  to  read  the  format  from\n"
 "              stdin you write \"@-\".\n"
 "\n"
-"              The  variables  present in the output format will be substituted\n"
-"              by the value or text that curl thinks fit, as  described  below.\n"
 , stdout);
  fputs(
+"              The  variables  present in the output format will be substituted\n"
+"              by the value or text that curl thinks fit, as  described  below.\n"
 "              All  variables are specified like %{variable_name} and to output\n"
 "              a normal % you just write them like %%. You can output a newline\n"
 "              by  using \\n, a carriage return with \\r and a tab space with \\t.\n"
 "              NOTE: The %-letter is a special letter in the win32-environment,\n"
+, stdout);
+ fputs(
 "              where  all  occurrences  of  %  must  be doubled when using this\n"
 "              option.\n"
 "\n"
 "              Available variables are at this point:\n"
 "\n"
-, stdout);
- fputs(
 "              url_effective  The URL that was fetched  last.  This  is  mostly\n"
 "                             meaningful  if  you’ve  told curl to follow loca‐\n"
 "                             tion: headers.\n"
 "\n"
 "              http_code      The numerical code that was  found  in  the  last\n"
 "                             retrieved HTTP(S) page.\n"
 "\n"
-"              http_connect   The  numerical  code  that  was found in the last\n"
-"                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 , stdout);
  fputs(
+"              http_connect   The  numerical  code  that  was found in the last\n"
+"                             response  (from  a  proxy)  to  a  curl   CONNECT\n"
 "                             request. (Added in 7.12.4)\n"
 "\n"
 "              time_total     The  total time, in seconds, that the full opera‐\n"
 "                             tion lasted. The time will be displayed with mil‐\n"
 "                             lisecond resolution.\n"
 "\n"
 "              time_namelookup\n"
+, stdout);
+ fputs(
 "                             The  time,  in  seconds,  it  took from the start\n"
 "                             until the name resolving was completed.\n"
 "\n"
-, stdout);
- fputs(
 "              time_connect   The time, in seconds,  it  took  from  the  start\n"
 "                             until  the  connect to the remote host (or proxy)\n"
 "                             was completed.\n"
 "\n"
 "              time_pretransfer\n"
 "                             The time, in seconds,  it  took  from  the  start\n"
-"                             until  the  file transfer is just about to begin.\n"
-"                             This includes all pre-transfer commands and nego‐\n"
 , stdout);
  fputs(
+"                             until  the  file transfer is just about to begin.\n"
+"                             This includes all pre-transfer commands and nego‐\n"
 "                             tiations that are specific to the particular pro‐\n"
 "                             tocol(s) involved.\n"
 "\n"
 "              time_redirect  The time, in seconds, it took for all redirection\n"
 "                             steps  include  name lookup, connect, pretransfer\n"
-"                             and  transfer  before   final   transaction   was\n"
-"                             started.  time_redirect shows the complete execu‐\n"
 , stdout);
  fputs(
+"                             and  transfer  before   final   transaction   was\n"
+"                             started.  time_redirect shows the complete execu‐\n"
 "                             tion time for multiple  redirections.  (Added  in\n"
 "                             7.12.3)\n"
 "\n"
 "              time_starttransfer\n"
 "                             The  time,  in  seconds,  it  took from the start\n"
-"                             until  the  first  byte  is  just  about  to   be\n"
-"                             transferred.  This  includes time_pretransfer and\n"
-"                             also the time the server needs to  calculate  the\n"
+"                             until the first byte is just about to  be  trans‐\n"
 , stdout);
  fputs(
+"                             ferred.  This  includes time_pretransfer and also\n"
+"                             the  time  the  server  needs  to  calculate  the\n"
 "                             result.\n"
 "\n"
 "              size_download  The total amount of bytes that were downloaded.\n"
 "\n"
 "              size_upload    The total amount of bytes that were uploaded.\n"
 "\n"
 "              size_header    The total amount of bytes of the downloaded head‐\n"
 "                             ers.\n"
 "\n"
+, stdout);
+ fputs(
 "              size_request   The total amount of bytes that were sent  in  the\n"
 "                             HTTP request.\n"
 "\n"
-, stdout);
- fputs(
 "              speed_download The average download speed that curl measured for\n"
 "                             the complete download.\n"
 "\n"
 "              speed_upload   The average upload speed that curl  measured  for\n"
 "                             the complete upload.\n"
 "\n"
 "              content_type   The  Content-Type  of  the requested document, if\n"
+, stdout);
+ fputs(
 "                             there was any.\n"
 "\n"
 "              num_connects   Number of new connects made in the recent  trans‐\n"
-, stdout);
- fputs(
 "                             fer. (Added in 7.12.3)\n"
 "\n"
 "              num_redirects  Number  of  redirects  that  were followed in the\n"
 "                             request. (Added in 7.12.3)\n"
 "\n"
 "              ftp_entry_path The initial path libcurl ended up in when logging\n"
 "                             on to the remote FTP server. (Added in 7.15.4)\n"
 "\n"
+, stdout);
+ fputs(
 "       If this option is used several times, the last one will be used.\n"
 "\n"
 "       -x/--proxy <proxyhost[:port]>\n"
-, stdout);
- fputs(
 "              Use  specified  HTTP proxy. If the port number is not specified,\n"
 "              it is assumed at port 1080.\n"
 "\n"
 "              This option overrides existing environment variables  that  sets\n"
 "              proxy  to  use.  If  there’s  an  environment variable setting a\n"
 "              proxy, you can set proxy to \"\" to override it.\n"
 "\n"
-"              Note that all operations that are performed over  a  HTTP  proxy\n"
 , stdout);
  fputs(
+"              Note that all operations that are performed over  a  HTTP  proxy\n"
 "              will  transparently  be converted to HTTP. It means that certain\n"
 "              protocol specific operations might not be available. This is not\n"
 "              the  case  if you can tunnel through the proxy, as done with the\n"
 "              -p/--proxytunnel option.\n"
 "\n"
 "              Starting with 7.14.1, the proxy host can be specified the  exact\n"
+, stdout);
+ fputs(
 "              same  way  as  the proxy environment variables, include protocol\n"
 "              prefix (http://) and embedded user + password.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X/--request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat‐\n"
 "              ing with the HTTP server.  The specified request  will  be  used\n"
 "              instead  of  the  method otherwise used (which defaults to GET).\n"
-"              Read the HTTP 1.1 specification for details and explanations.\n"
-"\n"
 , stdout);
  fputs(
+"              Read the HTTP 1.1 specification for details and explanations.\n"
+"\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with ftp.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -y/--speed-time <time>\n"
 "              If a download is slower than speed-limit bytes per second during\n"
 "              a speed-time period, the download gets aborted. If speed-time is\n"
-"              used, the default speed-limit will be 1 unless set with -y.\n"
-"\n"
 , stdout);
  fputs(
+"              used, the default speed-limit will be 1 unless set with -y.\n"
+"\n"
 "              This option controls transfers and thus  will  not  affect  slow\n"
 "              connects  etc.  If this is a concern for you, try the --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -Y/--speed-limit <speed>\n"
 "              If a download is slower than this given speed, in bytes per sec‐\n"
-"              ond, for speed-time seconds it gets aborted. speed-time  is  set\n"
 , stdout);
  fputs(
+"              ond, for speed-time seconds it gets aborted. speed-time  is  set\n"
 "              with -Y and is 30 if not set.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -z/--time-cond <date expression>\n"
 "              (HTTP/FTP) Request a file that has been modified later than  the\n"
 "              given  time  and date, or one that has been modified before that\n"
 "              time. The date expression can be all sorts of date strings or if\n"
-"              it  doesn’t  match  any  internal ones, it tries to get the time\n"
 , stdout);
  fputs(
+"              it  doesn’t  match  any  internal ones, it tries to get the time\n"
 "              from a given file name  instead!  See  the  curl_getdate(3)  man\n"
 "              pages for date expression details.\n"
 "\n"
 "              Start the date expression with a dash (-) to make it request for\n"
 "              a document that is older than the given date/time, default is  a\n"
 "              document that is newer than the specified date/time.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --max-redirs <num>\n"
-, stdout);
- fputs(
 "              Set  maximum  number  of  redirection-followings   allowed.   If\n"
 "              -L/--location  is  used, this option can be used to prevent curl\n"
 "              from following redirections \"in absurdum\". By default, the limit\n"
 "              is set to 50 redirections. Set this option to -1 to make it lim‐\n"
 "              itless.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -0/--http1.0\n"
-, stdout);
- fputs(
 "              (HTTP)  Forces curl to issue its requests using HTTP 1.0 instead\n"
 "              of using its internally preferred: HTTP 1.1.\n"
 "\n"
 "       -1/--tlsv1\n"
 "              (SSL) Forces curl to use TSL version 1 when negotiating  with  a\n"
 "              remote TLS server.\n"
 "\n"
 "       -2/--sslv2\n"
 "              (SSL)  Forces  curl to use SSL version 2 when negotiating with a\n"
 "              remote SSL server.\n"
+, stdout);
+ fputs(
 "\n"
 "       -3/--sslv3\n"
 "              (SSL) Forces curl to use SSL version 3 when negotiating  with  a\n"
-, stdout);
- fputs(
 "              remote SSL server.\n"
 "\n"
 "       -4/--ipv4\n"
 "              If  libcurl  is  capable  of resolving an address to multiple IP\n"
 "              versions (which it is if it is ipv6-capable), this option  tells\n"
 "              libcurl to resolve names to IPv4 addresses only.\n"
 "\n"
 "       -6/--ipv6\n"
 "              If  libcurl  is  capable  of resolving an address to multiple IP\n"
-"              versions (which it is if it is ipv6-capable), this option  tells\n"
 , stdout);
  fputs(
+"              versions (which it is if it is ipv6-capable), this option  tells\n"
 "              libcurl to resolve names to IPv6 addresses only.\n"
 "\n"
 "       -#/--progress-bar\n"
 "              Make curl display progress information as a progress bar instead\n"
 "              of the default statistics.\n"
 "\n"
