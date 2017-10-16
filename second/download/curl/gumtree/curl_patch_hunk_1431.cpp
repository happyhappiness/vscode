 "          If you start the data  with  the  letter  @,  the  rest\n"
 "          should  be  a  file name to read the data from, or - if\n"
 );
  puts(
 "          you want  curl  to  read  the  data  from  stdin.   The\n"
 "          contents  of the file must already be url-encoded. Mul­\n"
-"          tiple files can also be specified.\n"
+"          tiple files can also be specified. Posting data from  a\n"
+"          file  named  'foobar'  would  thus be done with \"--data\n"
+"          @foobar\".\n"
 "\n"
 "          To post data purely binary, you should instead use  the\n"
 "          --data-binary option.\n"
 "\n"
 "          -d/--data is the same as --data-ascii.\n"
 "\n"
 "          If  this option is used several times, the ones follow­\n"
+);
+ puts(
 "          ing the first will append data.\n"
 "\n"
 "     --data-ascii <data>\n"
-);
- puts(
 "          (HTTP) This is an alias for the -d/--data option.\n"
 "\n"
 "          If this option is used several times, the ones  follow­\n"
 "          ing the first will append data.\n"
 "\n"
 "     --data-binary <data>\n"
 "          (HTTP)  This  posts data in a similar manner as --data-\n"
 "          ascii does, although when using this option the  entire\n"
 "          context  of  the posted data is kept as-is. If you want\n"
-"          to post a binary file without the  strip-newlines  fea­\n"
 );
  puts(
+"          to post a binary file without the  strip-newlines  fea­\n"
 "          ture of the --data-ascii option, this is for you.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "          If this option is used several times, the ones  follow­\n"
 "          ing the first will append data.\n"
 "\n"
 "     -D/--dump-header <file>\n"
 "          (HTTP/FTP)  Write  the HTTP headers to this file. Write\n"
 "          the FTP file info to this file if -I/--head is used.\n"
 "\n"
-"          This option is handy to use when you want to store  the\n"
 );
  puts(
+"          This option is handy to use when you want to store  the\n"
 "          cookies  that  a  HTTP  site  sends to you. The cookies\n"
 "          could then be read in a second curl invoke by using the\n"
 "          -b/--cookie option!\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -e/--referer <URL>\n"
 "          (HTTP) Sends the \"Referer Page\" information to the HTTP\n"
 "          server.  This can also be set with the -H/--header flag\n"
-"          of course.  When used with -L/--location you can append\n"
 );
  puts(
+"          of course.  When used with -L/--location you can append\n"
 "          \";auto\"  to  the referer URL to make curl automatically\n"
 "          set the  previous  URL  when  it  follows  a  Location:\n"
 "          header.  The  \";auto\" string can be used alone, even if\n"
 "          you don't set an initial referer.\n"
-"\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     --egd-file <file>\n"
 "          (HTTPS)  Specify the path name to the Entropy Gathering\n"
-"          Daemon socket. The socket is used to  seed  the  random\n"
 );
  puts(
+"          Daemon socket. The socket is used to  seed  the  random\n"
 "          engine  for SSL connections. See also the --random-file\n"
 "          option.\n"
 "\n"
 "     -E/--cert <certificate[:password]>\n"
 "          (HTTPS) Tells curl to  use  the  specified  certificate\n"
 "          file  when  getting  a file with HTTPS. The certificate\n"
 "          must be in PEM format.  If the optional password  isn't\n"
 "          specified, it will be queried for on the terminal. Note\n"
+);
+ puts(
 "          that this certificate is the private key and  the  pri­\n"
 "          vate certificate concatenated!\n"
 "\n"
-);
- puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     --cacert <CA certificate>\n"
 "          (HTTPS) Tells curl to  use  the  specified  certificate\n"
 "          file to verify the peer. The certificate must be in PEM\n"
 "          format.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -f/--fail\n"
-"          (HTTP)  Fail  silently  (no  output  at  all) on server\n"
 );
  puts(
+"          (HTTP)  Fail  silently  (no  output  at  all) on server\n"
 "          errors. This is mostly done like this to better  enable\n"
 "          scripts  etc  to  better  deal with failed attempts. In\n"
 "          normal cases when a HTTP server fails to deliver a doc­\n"
 "          ument,  it  returns  a  HTML document stating so (which\n"
 "          often also describes why and more). This flag will pre­\n"
 "          vent  curl  from  outputting  that  and  fail  silently\n"
 "          instead.\n"
 "\n"
-"          If this option is used twice,  the  second  will  again\n"
 );
  puts(
+"          If this option is used twice,  the  second  will  again\n"
 "          disable silent failure.\n"
 "\n"
 "     -F/--form <name=content>\n"
 "          (HTTP) This lets curl emulate a filled in form in which\n"
 "          a user has pressed the submit button. This causes  curl\n"
 "          to POST data using the content-type multipart/form-data\n"
 "          according to RFC1867. This enables uploading of  binary\n"
 "          files etc. To force the 'content' part to be be a file,\n"
-"          prefix the file name with an @ sign. To  just  get  the\n"
 );
  puts(
+"          prefix the file name with an @ sign. To  just  get  the\n"
 "          content part from a file, prefix the file name with the\n"
 "          letter <. The difference between @ and < is then that @\n"
 "          makes a file get attached in the post as a file upload,\n"
-"          while the < makes a text field and just  get  the  con­\n"
-"          tents for that text field from a file.\n"
+"          while the <  makes  a  text  field  and  just  get  the\n"
+"          contents for that text field from a file.\n"
+"\n"
 "          Example,  to  send  your  password  file to the server,\n"
+);
+ puts(
 "          where 'password' is the name of the form-field to which\n"
 "          /etc/passwd will be the input:\n"
 "\n"
-);
- puts(
 "          curl -F password=@/etc/passwd www.mypasswords.com\n"
 "\n"
 "          To read the file's content from stdin insted of a file,\n"
 "          use - where the file name should've been. This goes for\n"
 "          both @ and < constructs.\n"
 "\n"
 "          This option can be used multiple times.\n"
 "\n"
 "     -g/--globoff\n"
 "          This  option  switches  off  the \"URL globbing parser\".\n"
-"          When you set this option, you  can  specify  URLs  that\n"
-"          contain  the  letters  {}[]  without  having them being\n"
 );
  puts(
+"          When you set this option, you  can  specify  URLs  that\n"
+"          contain  the  letters  {}[]  without  having them being\n"
 "          interpreted by curl itself. Note that these letters are\n"
 "          not  normal  legal  URL  contents  but  they  should be\n"
 "          encoded according to the URI standard. (Option added in\n"
 "          curl 7.6)\n"
 "\n"
+"     -G/--get\n"
+"          When  used,  this  option  will make all data specified\n"
+"          with -d/--data or --data-binary to be used  in  a  HTTP\n"
+);
+ puts(
+"          GET  request instead of the POST request that otherwise\n"
+"          would be used. The data will be  appended  to  the  URL\n"
+"          with a '?'  separator.\n"
+"\n"
 "     -h/--help\n"
 "          Usage help.\n"
 "\n"
 "     -H/--header <header>\n"
 "          (HTTP) Extra header to use when getting a web page. You\n"
 "          may specify any number of extra headers. Note  that  if\n"
 "          you  should  add a custom header that has the same name\n"
+"          as one of the internal ones curl would use, your exter­\n"
 );
  puts(
-"          as one of the internal ones curl would use, your exter­\n"
 "          nally  set  header will be used instead of the internal\n"
 "          one. This allows you to make even trickier  stuff  than\n"
 "          curl  would  normally do. You should not replace inter­\n"
 "          nally set headers without knowing perfectly  well  what\n"
 "          you're  doing.  Replacing  an  internal header with one\n"
 "          without content on the right side  of  the  colon  will\n"
-);
- puts(
 "          prevent that header from appearing.\n"
 "\n"
 "          This option can be used multiple times.\n"
 "\n"
+);
+ puts(
 "     -i/--include\n"
 "          (HTTP) Include the HTTP-header in the output. The HTTP-\n"
 "          header includes things like server-name,  date  of  the\n"
 "          document, HTTP-version and more...\n"
-"\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable header include.\n"
 "\n"
 "     --interface <name>\n"
 "          Perform an operation using a specified  interface.  You\n"
-);
- puts(
 "          can  enter  interface name, IP address or host name. An\n"
 "          example could look like:\n"
+"\n"
+);
+ puts(
 "          curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -I/--head\n"
 "          (HTTP/FTP)  Fetch  the  HTTP-header  only! HTTP-servers\n"
 "          feature the command HEAD which this uses to get nothing\n"
 "          but  the header of a document. When used on a FTP file,\n"
-);
- puts(
 "          curl displays the file size only.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
+);
+ puts(
 "          disable header only.\n"
 "\n"
 "     --krb4 <level>\n"
 "          (FTP)  Enable  kerberos4  authentication  and  use. The\n"
 "          level must be entered and should  be  one  of  'clear',\n"
 "          'safe',  'confidential'  or 'private'. Should you use a\n"
 "          level that is not one of these, 'private' will  instead\n"
 "          be used.\n"
 "\n"
-);
- puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -K/--config <config file>\n"
+);
+ puts(
 "          Specify which config file to read curl arguments  from.\n"
 "          The  config  file  is a text file in which command line\n"
 "          arguments can be written which then will be used as  if\n"
 "          they  were  written on the actual command line. Options\n"
 "          and their parameters must be specified on the same con­\n"
-);
- puts(
 "          fig  file  line.  If  the parameter is to contain white\n"
 "          spaces, the parameter must be inclosed  within  quotes.\n"
+);
+ puts(
 "          If  the  first column of a config line is a '#' charac­\n"
 "          ter, the rest of the line will be treated as a comment.\n"
 "\n"
 "          Specify  the filename as '-' to make curl read the file\n"
 "          from stdin.\n"
 "\n"
 "          This option can be used multiple times.\n"
 "\n"
 "     -l/--list-only\n"
 "          (FTP) When listing an FTP directory, this switch forces\n"
-);
- puts(
 "          a  name-only  view.   Especially  useful if you want to\n"
 "          machine-parse the contents of an  FTP  directory  since\n"
+);
+ puts(
 "          the  normal  directory view doesn't use a standard look\n"
 "          or format.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable list only.\n"
 "\n"
 "     -L/--location\n"
 "          (HTTP/HTTPS)  If  the server reports that the requested\n"
 "          page has  a  different  location  (indicated  with  the\n"
-);
- puts(
 "          header  line Location:) this flag will let curl attempt\n"
 "          to reattempt the get on the new place. If used together\n"
+);
+ puts(
 "          with -i or -I, headers from all requested pages will be\n"
 "          shown. If this flag is used when making  a  HTTP  POST,\n"
 "          curl will automatically switch to GET after the initial\n"
 "          POST has been done.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable location following.\n"
 "\n"
 "     -m/--max-time <seconds>\n"
-);
- puts(
 "          Maximum time in seconds that you allow the whole opera­\n"
 "          tion to take.  This is useful for preventing your batch\n"
+);
+ puts(
 "          jobs  from  hanging  for  hours due to slow networks or\n"
 "          links going down.  This doesn't  work  fully  in  win32\n"
 "          systems.  See also the --connect-timeout option.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -M/--manual\n"
 "          Manual. Display the huge help text.\n"
 "\n"
 "     -n/--netrc\n"
-);
- puts(
 "          Makes curl scan the .netrc  file  in  the  user's  home\n"
 "          directory  for  login  name and password. This is typi­\n"
+);
+ puts(
 "          cally used for ftp on unix. If  used  with  http,  curl\n"
 "          will  enable  user  authentication.  See  netrc(4)  for\n"
 "          details on the file format. Curl will not  complain  if\n"
 "          that  file  hasn't the right permissions (it should not\n"
 "          be world nor group readable). The environment  variable\n"
-);
- puts(
 "          \"HOME\" is used to find the home directory.\n"
 "\n"
 "          A  quick  and  very  simple  example  of how to setup a\n"
+);
+ puts(
 "          .netrc  to  allow  curl   to   ftp   to   the   machine\n"
 "          host.domain.com  with  user  name 'myself' and password\n"
 "          'secret' should look similar to:\n"
 "\n"
 "          machine host.domain.com login myself password secret\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable netrc usage.\n"
-"\n"
 "     -N/--no-buffer\n"
-);
- puts(
 "          Disables  the buffering of the output stream. In normal\n"
 "          work situations, curl will use a standard buffered out­\n"
+);
+ puts(
 "          put  stream that will have the effect that it will out­\n"
 "          put the data in chunks, not  necessarily  exactly  when\n"
 "          the  data arrives.  Using this option will disable that\n"
 "          buffering.\n"
+"\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          switch on buffering.\n"
 "\n"
 "     -o/--output <file>\n"
-);
- puts(
 "          Write  output  to  <file> instead of stdout. If you are\n"
 "          using {} or [] to fetch multiple documents, you can use\n"
+);
+ puts(
 "          '#'  followed by a number in the <file> specifier. That\n"
 "          variable will be replaced with the current  string  for\n"
 "          the URL being fetched. Like in:\n"
 "\n"
 "            curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
 "          or use several variables like:\n"
 "\n"
 "            curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
 "\n"
-);
- puts(
 "          You  may use this option as many times as you have num­\n"
 "          ber of URLs.\n"
 "\n"
 "     -O/--remote-name\n"
+);
+ puts(
 "          Write output to a local file named like the remote file\n"
 "          we get. (Only the file part of the remote file is used,\n"
 "          the path is cut off.)\n"
 "\n"
 "          You may use this option as many times as you have  num­\n"
 "          ber of URLs.\n"
 "\n"
 "     -p/--proxytunnel\n"
 "          When an HTTP proxy is used, this option will cause non-\n"
-);
- puts(
 "          HTTP protocols to attempt to tunnel through  the  proxy\n"
 "          instead  of merely using it to do HTTP-like operations.\n"
+);
+ puts(
 "          The tunnel approach is made with the HTTP proxy CONNECT\n"
 "          request  and requires that the proxy allows direct con­\n"
 "          nect to the remote port number  curl  wants  to  tunnel\n"
 "          through to.\n"
 "\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable proxy tunnel.\n"
 "\n"
 "     -P/--ftpport <address>\n"
-);
- puts(
 "          (FTP) Reverses the initiator/listener roles  when  con­\n"
 "          necting  with  ftp. This switch makes Curl use the PORT\n"
+);
+ puts(
 "          command instead of PASV. In practice,  PORT  tells  the\n"
 "          server to connect to the client's specified address and\n"
 "          port, while PASV asks the server for an ip address  and\n"
 "          port to connect to. <address> should be one of:\n"
 "\n"
 "          interface   i.e  \"eth0\" to specify which interface's IP\n"
-);
- puts(
 "                      address you want to use  (Unix only)\n"
 "\n"
 "          IP address  i.e \"192.168.10.1\" to specify exact IP num­\n"
 "                      ber\n"
+"\n"
+);
+ puts(
 "          host name   i.e \"my.host.domain\" to specify machine\n"
 "\n"
 "          -           (any  single-letter string) to make it pick\n"
 "                      the machine's default\n"
 "\n"
 "     If this option is used several times, the last one  will  be\n"
 "     used.\n"
 "\n"
 "     -q   If used as the first parameter on the command line, the\n"
-);
- puts(
 "          $HOME/.curlrc file will not be read and used as a  con­\n"
 "          fig file.\n"
 "\n"
 "     -Q/--quote <comand>\n"
 "          (FTP)  Send  an  arbitrary  command  to  the remote FTP\n"
+);
+ puts(
 "          server, by using the QUOTE command of the  server.  Not\n"
 "          all  servers support this command, and the set of QUOTE\n"
 "          commands are server specific! Quote commands  are  sent\n"
 "          BEFORE  the  transfer is taking place. To make commands\n"
-);
- puts(
 "          take place after a  successful  transfer,  prefix  them\n"
 "          with a dash '-'. You may specify any amount of commands\n"
 "          to be run before and after the transfer. If the  server\n"
+);
+ puts(
 "          returns  failure  for  one  of the commands, the entire\n"
 "          operation will be aborted.\n"
 "\n"
 "          This option can be used multiple times.\n"
 "\n"
 "     --random-file <file>\n"
 "          (HTTPS) Specify the path name to file  containing  what\n"
-);
- puts(
 "          will  be considered as random data. The data is used to\n"
 "          seed the random engine for SSL connections.   See  also\n"
 "          the --edg-file option.\n"
 "\n"
 "     -r/--range <range>\n"
+);
+ puts(
 "          (HTTP/FTP)  Retrieve  a byte range (i.e a partial docu­\n"
 "          ment) from a HTTP/1.1 or  FTP  server.  Ranges  can  be\n"
 "          specified in a number of ways.\n"
 "\n"
 "          0-499     specifies the first 500 bytes\n"
 "\n"
 "          500-999   specifies the second 500 bytes\n"
 "\n"
-);
- puts(
 "          -500      specifies the last 500 bytes\n"
-"\n"
 "          9500      specifies the bytes from offset 9500 and for­\n"
 "                    ward\n"
 "\n"
 "          0-0,-1    specifies the first and last byte only(*)(H)\n"
 "\n"
+);
+ puts(
 "          500-700,600-799\n"
 "                    specifies 300 bytes from offset 500(H)\n"
 "\n"
 "          100-199,500-599\n"
 "                    specifies two separate 100 bytes ranges(*)(H)\n"
 "\n"
 "     (*)  =  NOTE that this will cause the server to reply with a\n"
 "     multipart response!\n"
 "\n"
-);
- puts(
 "     You should also be aware that many HTTP/1.1 servers  do  not\n"
 "     have this feature enabled, so that when you attempt to get a\n"
 "     range, you'll instead get the whole document.\n"
 "\n"
+);
+ puts(
 "     FTP range downloads only support the simple  syntax  'start-\n"
 "     stop'  (optionally  with  one  of  the  numbers omitted). It\n"
 "     depends on the non-RFC command SIZE.\n"
 "\n"
 "     If this option is used several times, the last one  will  be\n"
 "     used.\n"
 "\n"
 "     -s/--silent\n"
-);
- puts(
 "          Silent  mode.  Don't  show progress meter or error mes­\n"
 "          sages.  Makes Curl mute.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable mute.\n"
 "\n"
 "     -S/--show-error\n"
+);
+ puts(
 "          When  used  with -s it makes curl show error message if\n"
 "          it fails.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
 "          disable show error.\n"
 "\n"
 "     -t/--telnet-option <OPT=val>\n"
 "          Pass  options to the telnet protocol. Supported options\n"
-);
- puts(
 "          are:\n"
 "\n"
 "          TTYPE=<term> Sets the terminal type.\n"
 "\n"
 "          XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
 "          NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
 "     -T/--upload-file <file>\n"
+);
+ puts(
 "          Like -t, but this transfers the specified  local  file.\n"
 "          If  there  is  no  file part in the specified URL, Curl\n"
 "          will append the local file name. NOTE that you must use\n"
 "          a  trailing  / on the last directory to really prove to\n"
-);
- puts(
 "          Curl that there is no file name or curl will think that\n"
 "          your  last  directory  name  is the remote file name to\n"
 "          use. That will most likely cause the  upload  operation\n"
+);
+ puts(
 "          to  fail.  If this is used on a http(s) server, the PUT\n"
 "          command will be used.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -u/--user <user:password>\n"
 "          Specify  user  and  password  to use when fetching. See\n"
-);
- puts(
 "          README.curl for detailed examples of how to  use  this.\n"
 "          If  no  password  is  specified,  curl  will ask for it\n"
 "          interactively.\n"
 "\n"
+);
+ puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -U/--proxy-user <user:password>\n"
 "          Specify  user and password to use for Proxy authentica­\n"
 "          tion. If no password is specified, curl will ask for it\n"
 "          interactively.\n"
 "\n"
-);
- puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     --url <URL>\n"
 "          Specify a URL to fetch. This  option  is  mostly  handy\n"
+);
+ puts(
 "          when you wanna specify URL(s) in a config file.\n"
 "\n"
 "          This option may be used any number of times. To control\n"
 "          where this URL  is  written,  use  the  -o  or  the  -O\n"
 "          options.\n"
 "\n"
 "     -v/--verbose\n"
 "          Makes   the  fetching  more  verbose/talkative.  Mostly\n"
-);
- puts(
 "          usable for debugging. Lines  starting  with  '>'  means\n"
 "          data sent by curl, '<' means data received by curl that\n"
 "          is hidden in normal cases and lines starting  with  '*'\n"
+);
+ puts(
 "          means additional info provided by curl.\n"
 "\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable verbose.\n"
 "\n"
 "     -V/--version\n"
 "          Displays the full version of curl,  libcurl  and  other\n"
 "          3rd party libraries linked with the executable.\n"
 "\n"
+"     -w/--write-out <format>\n"
+"          Defines   what   to   display  after  a  completed  and\n"
+"          successful operation. The format is a string  that  may\n"
 );
  puts(
-"     -w/--write-out <format>\n"
-"          Defines  what to display after a completed and success­\n"
-"          ful operation. The format is a string that may  contain\n"
-"          plain  text  mixed  with  any  number of variables. The\n"
-"          string can be specified as \"string\", to get read from a\n"
-"          particular  file you specify it \"@filename\" and to tell\n"
-"          curl to read the format from stdin you write \"@-\".\n"
+"          contain  plain text mixed with any number of variables.\n"
+"          The string can be specified as \"string\",  to  get  read\n"
+"          from  a  particular file you specify it \"@filename\" and\n"
+"          to tell curl to read the format from  stdin  you  write\n"
+"          \"@-\".\n"
 "\n"
 "          The variables present in the output format will be sub­\n"
+"          stituted by the value or text that curl thinks fit,  as\n"
+"          described  below.  All  variables  are  specified  like\n"
 );
  puts(
-"          stituted  by the value or text that curl thinks fit, as\n"
-"          described  below.  All  variables  are  specified  like\n"
-"          %{variable_name}  and  to  output  a  normal % you just\n"
-"          write them like %%. You can output a newline  by  using\n"
+"          %{variable_name} and to output  a  normal  %  you  just\n"
+"          write  them  like %%. You can output a newline by using\n"
 "          \\n, a carrige return with \\r and a tab space with \\t.\n"
 "\n"
-"          NOTE:   The   %-letter  is  a  special  letter  in  the\n"
-"          win32-environment, where all occurrences of %  must  be\n"
-);
- puts(
+"          NOTE:  The  %-letter  is  a  special  letter   in   the\n"
+"          win32-environment,  where  all occurrences of % must be\n"
 "          doubled when using this option.\n"
 "\n"
 "          Available variables are at this point:\n"
 "\n"
-"          url_effective  The  URL  that was fetched last. This is\n"
+"          url_effective  The URL that was fetched last.  This  is\n"
+);
+ puts(
 "                         mostly meaningful if you've told curl to\n"
 "                         follow location: headers.\n"
 "\n"
 "          http_code      The numerical code that was found in the\n"
 "                         last retrieved HTTP(S) page.\n"
 "\n"
-"          time_total     The total time,  in  seconds,  that  the\n"
-);
- puts(
-"                         full  operation lasted. The time will be\n"
+"          time_total     The  total  time,  in  seconds, that the\n"
+"                         full operation lasted. The time will  be\n"
 "                         displayed with millisecond resolution.\n"
 "\n"
 "          time_namelookup\n"
-"                         The time, in seconds, it took  from  the\n"
-"                         start  until the name resolving was com­\n"
-"                         pleted.\n"
-"\n"
-"          time_connect   The time, in seconds, it took  from  the\n"
-"                         start  until  the  connect to the remote\n"
 );
  puts(
+"                         The  time,  in seconds, it took from the\n"
+"                         start until the name resolving was  com­\n"
+"                         pleted.\n"
+"\n"
+"          time_connect   The  time,  in seconds, it took from the\n"
+"                         start until the connect  to  the  remote\n"
 "                         host (or proxy) was completed.\n"
 "\n"
 "          time_pretransfer\n"
-"                         The time, in seconds, it took  from  the\n"
-"                         start  until  the  file transfer is just\n"
-"                         about to begin. This includes  all  pre-\n"
-"                         transfer  commands and negotiations that\n"
-"                         are specific to  the  particular  proto­\n"
-"                         col(s) involved.\n"
-"\n"
+"                         The  time,  in seconds, it took from the\n"
 );
  puts(
-"          size_download  The  total  amount  of  bytes  that were\n"
+"                         start until the file  transfer  is  just\n"
+"                         about  to  begin. This includes all pre-\n"
+"                         transfer commands and negotiations  that\n"
+"                         are  specific  to  the particular proto­\n"
+"                         col(s) involved.\n"
+"\n"
+"          size_download  The total  amount  of  bytes  that  were\n"
 "                         downloaded.\n"
 "\n"
-"          size_upload    The total  amount  of  bytes  that  were\n"
+"          size_upload    The  total  amount  of  bytes  that were\n"
+);
+ puts(
 "                         uploaded.\n"
 "\n"
-"          size_header    The  total  amount of bytes of the down­\n"
+"          size_header    The total amount of bytes of  the  down­\n"
 "                         loaded headers.\n"
 "\n"
 "          size_request   The total amount of bytes that were sent\n"
 "                         in the HTTP request.\n"
 "\n"
-"          speed_download The  average  download  speed  that curl\n"
+"          speed_download The average  download  speed  that  curl\n"
+"                         measured for the complete download.\n"
+"\n"
+"          speed_upload   The  average upload speed that curl mea­\n"
 );
  puts(
-"                         measured for the complete download.\n"
-"          speed_upload   The average upload speed that curl  mea­\n"
 "                         sured for the complete upload.\n"
 "\n"
-"     If  this  option is used several times, the last one will be\n"
+"     If this option is used several times, the last one  will  be\n"
 "     used.\n"
 "\n"
 "     -x/--proxy <proxyhost[:port]>\n"
-"          Use specified proxy. If the port number is  not  speci­\n"
+"          Use  specified  proxy. If the port number is not speci­\n"
 "          fied, it is assumed at port 1080.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
+"     -X/--request <command>\n"
+"          (HTTP)  Specifies a custom request to use when communi­\n"
 );
  puts(
-"     -X/--request <command>\n"
-"          (HTTP) Specifies a custom request to use when  communi­\n"
-"          cating  with  the  HTTP  server.  The specified request\n"
+"          cating with the HTTP  server.   The  specified  request\n"
 "          will be used instead of the standard GET. Read the HTTP\n"
 "          1.1 specification for details and explanations.\n"
 "\n"
-"          (FTP)  Specifies a custom FTP command to use instead of\n"
+"          (FTP) Specifies a custom FTP command to use instead  of\n"
 "          LIST when doing file lists with ftp.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
-);
- puts(
 "     -y/--speed-time <time>\n"
 "          If a download is slower than speed-limit bytes per sec­\n"
-"          ond during  a  speed-time  period,  the  download  gets\n"
+);
+ puts(
+"          ond  during  a  speed-time  period,  the  download gets\n"
 "          aborted. If speed-time is used, the default speed-limit\n"
 "          will be 1 unless set with -y.\n"
 "\n"
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -Y/--speed-limit <speed>\n"
 "          If a download is slower than this given speed, in bytes\n"
-);
- puts(
-"          per second, for speed-time  seconds  it  gets  aborted.\n"
+"          per  second,  for  speed-time  seconds it gets aborted.\n"
 "          speed-time is set with -Y and is 30 if not set.\n"
 "\n"
+);
+ puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
-"\n"
 "     -z/--time-cond <date expression>\n"
-"          (HTTP) Request to get a file  that  has  been  modified\n"
-"          later  than  the  given  time and date, or one that has\n"
+"          (HTTP)  Request  to  get  a file that has been modified\n"
+"          later than the given time and date,  or  one  that  has\n"
 "          been modified before that time. The date expression can\n"
+"          be all sorts of date strings or if it doesn't match any\n"
+"          internal  ones,  it  tries to get the time from a given\n"
 );
  puts(
-"          be all sorts of date strings or if it doesn't match any\n"
-"          internal ones, it tries to get the time  from  a  given\n"
-"          file  name  instead!  See  the GNU date(1) or curl_get­\n"
+"          file name instead! See the  GNU  date(1)  or  curl_get­\n"
 "          date(3) man pages for date expression details.\n"
 "\n"
-"          Start the date expression with a dash (-)  to  make  it\n"
-"          request  for  a  document  that is older than the given\n"
+"          Start  the  date  expression with a dash (-) to make it\n"
+"          request for a document that is  older  than  the  given\n"
 "          date/time, default is a document that is newer than the\n"
 "          specified date/time.\n"
 "\n"
-);
- puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "     -3/--sslv3\n"
+);
+ puts(
 "          (HTTPS) Forces curl to use SSL version 3 when negotiat­\n"
 "          ing with a remote SSL server.\n"
 "\n"
 "     -2/--sslv2\n"
 "          (HTTPS) Forces curl to use SSL version 2 when negotiat­\n"
 "          ing with a remote SSL server.\n"
 "\n"
 "     -#/--progress-bar\n"
-"          Make curl display progress information  as  a  progress\n"
+"          Make  curl  display  progress information as a progress\n"
 "          bar instead of the default statistics.\n"
 "\n"
-);
- puts(
-"          If  this  option  is  used twice, the second will again\n"
+"          If this option is used twice,  the  second  will  again\n"
 "          disable the progress bar.\n"
 "\n"
 "     --crlf\n"
-"          (FTP) Convert LF to CRLF  in  upload.  Useful  for  MVS\n"
+);
+ puts(
+"          (FTP)  Convert  LF  to  CRLF  in upload. Useful for MVS\n"
 "          (OS/390).\n"
 "\n"
-"          If  this  option  is  used twice, the second will again\n"
+"          If this option is used twice,  the  second  will  again\n"
 "          disable crlf converting.\n"
 "\n"
 "     --stderr <file>\n"
-"          Redirect all writes to stderr  to  the  specified  file\n"
+"          Redirect  all  writes  to  stderr to the specified file\n"
 "          instead. If the file name is a plain '-', it is instead\n"
-);
- puts(
 "          written to stdout. This option has no point when you're\n"
 "          using a shell with decent redirecting capabilities.\n"
 "\n"
+);
+ puts(
 "          If this option is used several times, the last one will\n"
 "          be used.\n"
 "\n"
 "FILES\n"
 "     ~/.curlrc\n"
 "          Default config file.\n"
-"\n"
 "ENVIRONMENT\n"
 "     HTTP_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for HTTP.\n"
 "\n"
 "     HTTPS_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for HTTPS.\n"
 "\n"
-);
- puts(
 "     FTP_PROXY [protocol://]<host>[:port]\n"
 "          Sets proxy server to use for FTP.\n"
+"\n"
 "     GOPHER_PROXY [protocol://]<host>[:port]\n"
+);
+ puts(
 "          Sets proxy server to use for GOPHER.\n"
 "\n"
 "     ALL_PROXY [protocol://]<host>[:port]\n"
-"          Sets proxy server to use if no protocol-specific  proxy\n"
+"          Sets  proxy server to use if no protocol-specific proxy\n"
 "          is set.\n"
 "\n"
 "     NO_PROXY <comma-separated list of hosts>\n"
 "          list of host names that shouldn't go through any proxy.\n"
 "          If set to a asterisk '*' only, it matches all hosts.\n"
 "\n"
-);
- puts(
 "     COLUMNS <integer>\n"
-"          The width of the terminal.  This variable only  affects\n"
+"          The  width of the terminal.  This variable only affects\n"
 "          curl when the --progress-bar option is used.\n"
 "\n"
+);
+ puts(
 "EXIT CODES\n"
 "     There exists a bunch of different error codes and their cor­\n"
-"     responding error messages that may appear during bad  condi­\n"
+"     responding  error messages that may appear during bad condi­\n"
 "     tions. At the time of this writing, the exit codes are:\n"
 "\n"
 "     1    Unsupported protocol. This build of curl has no support\n"
 "          for this protocol.\n"
 "\n"
 "     2    Failed to initialize.\n"
 "\n"
-);
- puts(
 "     3    URL malformat. The syntax was not correct.\n"
 "\n"
-"     4    URL user malformatted. The user-part of the URL  syntax\n"
+"     4    URL  user malformatted. The user-part of the URL syntax\n"
 "          was not correct.\n"
 "\n"
-"     5    Couldn't  resolve proxy. The given proxy host could not\n"
+);
+ puts(
+"     5    Couldn't resolve proxy. The given proxy host could  not\n"
 "          be resolved.\n"
 "\n"
-"     6    Couldn't resolve host. The given remote  host  was  not\n"
+"     6    Couldn't  resolve  host.  The given remote host was not\n"
 "          resolved.\n"
 "\n"
 "     7    Failed to connect to host.\n"
 "\n"
-"     8    FTP  weird  server  reply.  The  server  sent data curl\n"
+"     8    FTP weird server  reply.  The  server  sent  data  curl\n"
 "          couldn't parse.\n"
 "\n"
-);
- puts(
 "     9    FTP access denied. The server denied login.\n"
-"\n"
-"     10   FTP user/password incorrect. Either one  or  both  were\n"
+"     10   FTP  user/password  incorrect.  Either one or both were\n"
 "          not accepted by the server.\n"
 "\n"
-"     11   FTP  weird  PASS  reply.  Curl couldn't parse the reply\n"
+);
+ puts(
+"     11   FTP weird PASS reply. Curl  couldn't  parse  the  reply\n"
 "          sent to the PASS request.\n"
 "\n"
-"     12   FTP weird USER reply. Curl  couldn't  parse  the  reply\n"
+"     12   FTP  weird  USER  reply.  Curl couldn't parse the reply\n"
 "          sent to the USER request.\n"
-"     13   FTP  weird  PASV  reply,  Curl couldn't parse the reply\n"
+"\n"
+"     13   FTP weird PASV reply, Curl  couldn't  parse  the  reply\n"
 "          sent to the PASV request.\n"
 "\n"
-);
- puts(
-"     14   FTP weird 227 format. Curl couldn't parse the  227-line\n"
+"     14   FTP  weird 227 format. Curl couldn't parse the 227-line\n"
 "          the server sent.\n"
 "\n"
 "     15   FTP can't get host. Couldn't resolve the host IP we got\n"
 "          in the 227-line.\n"
 "\n"
-"     16   FTP can't reconnect. Couldn't connect to  the  host  we\n"
+);
+ puts(
+"     16   FTP  can't  reconnect.  Couldn't connect to the host we\n"
 "          got in the 227-line.\n"
 "\n"
 "     17   FTP  couldn't  set  binary.  Couldn't  change  transfer\n"
 "          method to binary.\n"
 "\n"
 "     18   Partial file. Only a part of the file was transfered.\n"
 "\n"
-);
- puts(
 "     19   FTP couldn't RETR file. The RETR command failed.\n"
 "\n"
-"     20   FTP write error. The transfer was reported bad  by  the\n"
+"     20   FTP  write  error. The transfer was reported bad by the\n"
 "          server.\n"
 "\n"
-"     21   FTP  quote  error.  A quote command returned error from\n"
+"     21   FTP quote error. A quote command  returned  error  from\n"
 "          the server.\n"
 "\n"
-"     22   HTTP not found. The requested page was not found.  This\n"
+);
+ puts(
+"     22   HTTP  not found. The requested page was not found. This\n"
 "          return code only appears if --fail is used.\n"
 "\n"
-"     23   Write  error.  Curl  couldn't  write  data  to  a local\n"
+"     23   Write error.  Curl  couldn't  write  data  to  a  local\n"
 "          filesystem or similar.\n"
 "\n"
-);
- puts(
 "     24   Malformat user. User name badly specified.\n"
 "\n"
-"     25   FTP couldn't STOR file.  The  server  denied  the  STOR\n"
+"     25   FTP  couldn't  STOR  file.  The  server denied the STOR\n"
 "          operation.\n"
 "\n"
 "     26   Read error. Various reading problems.\n"
 "\n"
 "     27   Out of memory. A memory allocation request failed.\n"
 "\n"
-"     28   Operation  timeout.  The  specified time-out period was\n"
+);
+ puts(
+"     28   Operation timeout. The specified  time-out  period  was\n"
 "          reached according to the conditions.\n"
-"\n"
-"     29   FTP couldn't set ASCII. The server returned an  unknown\n"
+"     29   FTP  couldn't set ASCII. The server returned an unknown\n"
 "          reply.\n"
 "\n"
-);
- puts(
 "     30   FTP PORT failed. The PORT command failed.\n"
 "\n"
 "     31   FTP couldn't use REST. The REST command failed.\n"
 "\n"
-"     32   FTP  couldn't  use  SIZE.  The SIZE command failed. The\n"
-"          command is an extension to the original  FTP  spec  RFC\n"
+"     32   FTP couldn't use SIZE. The  SIZE  command  failed.  The\n"
+"          command  is  an  extension to the original FTP spec RFC\n"
 "          959.\n"
 "\n"
+);
+ puts(
 "     33   HTTP range error. The range \"command\" didn't work.\n"
 "\n"
-"     34   HTTP   post  error.  Internal  post-request  generation\n"
+"     34   HTTP  post  error.  Internal  post-request   generation\n"
 "          error.\n"
 "\n"
 "     35   SSL connect error. The SSL handshaking failed.\n"
 "\n"
-);
- puts(
-"     36   FTP bad download resume. Couldn't continue  an  earlier\n"
+"     36   FTP  bad  download resume. Couldn't continue an earlier\n"
 "          aborted download.\n"
 "\n"
-"     37   FILE  couldn't read file. Failed to open the file. Per­\n"
+"     37   FILE couldn't read file. Failed to open the file.  Per­\n"
 "          missions?\n"
 "\n"
 "     38   LDAP cannot bind. LDAP bind operation failed.\n"
 "\n"
 "     39   LDAP search failed.\n"
 "\n"
+);
+ puts(
 "     40   Library not found. The LDAP library was not found.\n"
 "\n"
-"     41   Function not found. A required LDAP  function  was  not\n"
+"     41   Function  not  found.  A required LDAP function was not\n"
 "          found.\n"
 "\n"
-"     42   Aborted  by callback. An application told curl to abort\n"
-);
- puts(
+"     42   Aborted by callback. An application told curl to  abort\n"
 "          the operation.\n"
 "\n"
 "     43   Internal error. A function was called with a bad param­\n"
 "          eter.\n"
 "\n"
 "     44   Internal error. A function was called in a bad order.\n"
 "\n"
-"     45   Interface  error.  A specified outgoing interface could\n"
+"     45   Interface error. A specified outgoing  interface  could\n"
 "          not be used.\n"
 "\n"
-"     46   Bad password entered. An error was signalled  when  the\n"
+);
+ puts(
+"     46   Bad  password  entered. An error was signalled when the\n"
 "          password was entered.\n"
 "\n"
-"     47   Too  many redirects. When following redirects, curl hit\n"
+"     47   Too many redirects. When following redirects, curl  hit\n"
 "          the maximum amount.\n"
 "\n"
-);
- puts(
 "     48   Unknown TELNET option specified.\n"
-"\n"
 "     49   Malformed telnet option.\n"
 "\n"
-"     XX   There will appear  more  error  codes  here  in  future\n"
-"          releases.  The existing ones are meant to never change.\n"
+"     XX   There  will  appear  more  error  codes  here in future\n"
+"          releases. The existing ones are meant to never  change.\n"
 "\n"
 "BUGS\n"
 "     If you do find bugs, mail them to curl-bug@haxx.se.\n"
+"\n"
 "AUTHORS / CONTRIBUTORS\n"
-"     Daniel Stenberg is the main author, but the  whole  list  of\n"
+);
+ puts(
+"     Daniel  Stenberg  is  the main author, but the whole list of\n"
 "     contributors is found in the separate THANKS file.\n"
 "\n"
 "WWW\n"
 "     http://curl.haxx.se\n"
 "\n"
 "FTP\n"
-);
- puts(
 "     ftp://ftp.sunet.se/pub/www/utilities/curl/\n"
 "\n"
 "SEE ALSO\n"
 "     ftp(1), wget(1), snarf(1)\n"
 "\n"
 "LATEST VERSION\n"
