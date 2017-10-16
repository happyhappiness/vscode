 );
  puts(
 "          specified, it will be queried for on the terminal. Note\n"
 "          that  this  certificate is the private key and the pri­\n"
 "          vate certificate concatenated!\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     --cacert <CA certificate>\n"
 "          (HTTPS)  Tells  curl  to  use the specified certificate\n"
 "          file to verify the peer. The certificate must be in PEM\n"
 "          format.\n"
 "\n"
 );
  puts(
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -f/--fail\n"
 "          (HTTP) Fail silently  (no  output  at  all)  on  server\n"
 "          errors.  This is mostly done like this to better enable\n"
 "          scripts etc to better deal  with  failed  attempts.  In\n"
 "          normal cases when a HTTP server fails to deliver a doc­\n"
 "          ument, it returns a HTML  document  stating  so  (which\n"
+"          often also describes why and more). This flag will pre­\n"
 );
  puts(
-"          often also describes why and more). This flag will pre­\n"
 "          vent  curl  from  outputting  that  and  fail  silently\n"
 "          instead.\n"
 "\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable silent failure.\n"
 "\n"
 "     -F/--form <name=content>\n"
 "          (HTTP) This lets curl emulate a filled in form in which\n"
 "          a  user has pressed the submit button. This causes curl\n"
 "          to POST data using the content-type multipart/form-data\n"
+"          according  to RFC1867. This enables uploading of binary\n"
 );
  puts(
-"          according  to RFC1867. This enables uploading of binary\n"
 "          files etc. To force the 'content' part to be be a file,\n"
 "          prefix  the  file  name with an @ sign. To just get the\n"
 "          content part from a file, prefix the file name with the\n"
 "          letter <. The difference between @ and < is then that @\n"
 "          makes a file get attached in the post as a file upload,\n"
 "          while  the  <  makes a text field and just get the con­\n"
+"          tents for that text field from a file.\n"
 );
  puts(
-"          tents for that text field from a file.\n"
 "          Example, to send your  password  file  to  the  server,\n"
 "          where 'password' is the name of the form-field to which\n"
 "          /etc/passwd will be the input:\n"
 "\n"
 "          curl -F password=@/etc/passwd www.mypasswords.com\n"
 "\n"
 "          To read the file's content from stdin insted of a file,\n"
 "          use - where the file name should've been. This goes for\n"
 "          both @ and < constructs.\n"
 "\n"
-);
- puts(
 "          This option can be used multiple times.\n"
 "\n"
 "     -g/--globoff\n"
+);
+ puts(
 "          This option switches off  the  \"URL  globbing  parser\".\n"
 "          When  you  set  this  option, you can specify URLs that\n"
 "          contain the letters  {}[]  without  having  them  being\n"
 "          interpreted by curl itself. Note that these letters are\n"
 "          not normal  legal  URL  contents  but  they  should  be\n"
 "          encoded according to the URI standard. (Option added in\n"
 "          curl 7.6)\n"
 "\n"
-);
- puts(
 "     -h/--help\n"
 "          Usage help.\n"
 "\n"
 "     -H/--header <header>\n"
+);
+ puts(
 "          (HTTP) Extra header to use when getting a web page. You\n"
 "          may  specify  any number of extra headers. Note that if\n"
 "          you should add a custom header that has the  same  name\n"
 "          as one of the internal ones curl would use, your exter­\n"
 "          nally set header will be used instead of  the  internal\n"
 "          one.  This  allows you to make even trickier stuff than\n"
+"          curl would normally do. You should not  replace  inter­\n"
 );
  puts(
-"          curl would normally do. You should not  replace  inter­\n"
 "          nally  set  headers without knowing perfectly well what\n"
 "          you're doing. Replacing an  internal  header  with  one\n"
 "          without  content  on  the  right side of the colon will\n"
 "          prevent that header from appearing.\n"
 "\n"
 "          This option can be used multiple times.\n"
 "\n"
 "     -i/--include\n"
 "          (HTTP) Include the HTTP-header in the output. The HTTP-\n"
-);
- puts(
 "          header  includes  things  like server-name, date of the\n"
 "          document, HTTP-version and more...\n"
 "\n"
+);
+ puts(
 "          If this option is used twice,  the  second  will  again\n"
 "          disable header include.\n"
 "\n"
 "     --interface <name>\n"
 "          Perform  an  operation using a specified interface. You\n"
 "          can enter interface name, IP address or host  name.  An\n"
 "          example could look like:\n"
 "          curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
-);
- puts(
-"          If  this  option  is  used serveral times, the last one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -I/--head\n"
+);
+ puts(
 "          (HTTP/FTP) Fetch  the  HTTP-header  only!  HTTP-servers\n"
 "          feature the command HEAD which this uses to get nothing\n"
 "          but the header of a document. When used on a FTP  file,\n"
 "          curl displays the file size only.\n"
 "\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable header only.\n"
 "\n"
 "     --krb4 <level>\n"
-);
- puts(
 "          (FTP) Enable  kerberos4  authentication  and  use.  The\n"
 "          level  must  be  entered  and should be one of 'clear',\n"
+);
+ puts(
 "          'safe', 'confidential' or 'private'. Should you  use  a\n"
 "          level  that is not one of these, 'private' will instead\n"
 "          be used.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -K/--config <config file>\n"
 "          Specify  which config file to read curl arguments from.\n"
-);
- puts(
 "          The config file is a text file in  which  command  line\n"
 "          arguments  can be written which then will be used as if\n"
+);
+ puts(
 "          they were written on the actual command  line.  Options\n"
 "          and their parameters must be specified on the same con­\n"
 "          fig file line. If the parameter  is  to  contain  white\n"
 "          spaces,  the  parameter must be inclosed within quotes.\n"
 "          If the first column of a config line is a  '#'  charac­\n"
-);
- puts(
 "          ter, the rest of the line will be treated as a comment.\n"
 "\n"
 "          Specify the filename as '-' to make curl read the  file\n"
 "          from stdin.\n"
 "\n"
+);
+ puts(
 "          This option can be used multiple times.\n"
 "\n"
 "     -l/--list-only\n"
 "          (FTP) When listing an FTP directory, this switch forces\n"
 "          a name-only view.  Especially useful  if  you  want  to\n"
 "          machine-parse  the  contents  of an FTP directory since\n"
 "          the normal directory view doesn't use a  standard  look\n"
-);
- puts(
 "          or format.\n"
 "\n"
 "          If  this  option  is  used twice, the second will again\n"
 "          disable list only.\n"
 "\n"
 "     -L/--location\n"
+);
+ puts(
 "          (HTTP/HTTPS) If the server reports that  the  requested\n"
 "          page  has  a  different  location  (indicated  with the\n"
 "          header line Location:) this flag will let curl  attempt\n"
 "          to reattempt the get on the new place. If used together\n"
 "          with -i or -I, headers from all requested pages will be\n"
-);
- puts(
 "          shown.  If  this  flag is used when making a HTTP POST,\n"
 "          curl will automatically switch to GET after the initial\n"
 "          POST has been done.\n"
 "\n"
+);
+ puts(
 "          If  this  option  is  used twice, the second will again\n"
 "          disable location following.\n"
 "\n"
 "     -m/--max-time <seconds>\n"
 "          Maximum time in seconds that you allow the whole opera­\n"
 "          tion to take.  This is useful for preventing your batch\n"
 "          jobs from hanging for hours due  to  slow  networks  or\n"
-);
- puts(
 "          links  going  down.   This  doesn't work fully in win32\n"
 "          systems.  See also the --connect-timeout option.\n"
 "\n"
-"          If this option is used serveral  times,  the  last  one\n"
-"          will be used.\n"
+);
+ puts(
+"          If this option is used several times, the last one will\n"
+"          be used.\n"
 "\n"
 "     -M/--manual\n"
 "          Manual. Display the huge help text.\n"
 "\n"
 "     -n/--netrc\n"
 "          Makes  curl  scan  the  .netrc  file in the user's home\n"
 "          directory for login name and password.  This  is  typi­\n"
 "          cally  used  for  ftp  on unix. If used with http, curl\n"
-);
- puts(
 "          will  enable  user  authentication.  See  netrc(4)  for\n"
 "          details  on  the file format. Curl will not complain if\n"
+);
+ puts(
 "          that file hasn't the right permissions (it  should  not\n"
 "          be  world nor group readable). The environment variable\n"
 "          \"HOME\" is used to find the home directory.\n"
 "\n"
 "          A quick and very simple  example  of  how  to  setup  a\n"
 "          .netrc   to   allow   curl   to   ftp  to  the  machine\n"
-);
- puts(
 "          host.domain.com with user name  'myself'  and  password\n"
 "          'secret' should look similar to:\n"
 "\n"
 "          machine host.domain.com login myself password secret\n"
 "\n"
+);
+ puts(
 "          If  this  option  is  used twice, the second will again\n"
 "          disable netrc usage.\n"
 "\n"
 "     -N/--no-buffer\n"
 "          Disables the buffering of the output stream. In  normal\n"
 "          work situations, curl will use a standard buffered out­\n"
 "          put stream that will have the effect that it will  out­\n"
-);
- puts(
 "          put  the  data  in chunks, not necessarily exactly when\n"
 "          the data arrives.  Using this option will disable  that\n"
 "          buffering.\n"
+);
+ puts(
 "          If  this  option  is  used twice, the second will again\n"
 "          switch on buffering.\n"
 "\n"
 "     -o/--output <file>\n"
 "          Write output to <file> instead of stdout.  If  you  are\n"
 "          using {} or [] to fetch multiple documents, you can use\n"
 "          '#' followed by a number in the <file> specifier.  That\n"
-);
- puts(
 "          variable  will  be replaced with the current string for\n"
 "          the URL being fetched. Like in:\n"
 "\n"
 "            curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
+);
+ puts(
 "          or use several variables like:\n"
 "\n"
 "            curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
 "\n"
 "          You may use this option as many times as you have  num­\n"
 "          ber of URLs.\n"
 "\n"
 "     -O/--remote-name\n"
 "          Write output to a local file named like the remote file\n"
-);
- puts(
 "          we get. (Only the file part of the remote file is used,\n"
 "          the path is cut off.)\n"
 "\n"
 "          You  may use this option as many times as you have num­\n"
 "          ber of URLs.\n"
 "\n"
 "     -p/--proxytunnel\n"
+);
+ puts(
 "          When an HTTP proxy is used, this option will cause non-\n"
 "          HTTP  protocols  to attempt to tunnel through the proxy\n"
 "          instead of merely using it to do HTTP-like  operations.\n"
 "          The tunnel approach is made with the HTTP proxy CONNECT\n"
-);
- puts(
 "          request and requires that the proxy allows direct  con­\n"
 "          nect  to  the  remote  port number curl wants to tunnel\n"
 "          through to.\n"
 "\n"
 "          If this option is used twice,  the  second  will  again\n"
+);
+ puts(
 "          disable proxy tunnel.\n"
 "\n"
 "     -P/--ftpport <address>\n"
 "          (FTP)  Reverses  the initiator/listener roles when con­\n"
 "          necting with ftp. This switch makes Curl use  the  PORT\n"
 "          command  instead  of  PASV. In practice, PORT tells the\n"
-);
- puts(
 "          server to connect to the client's specified address and\n"
 "          port,  while PASV asks the server for an ip address and\n"
 "          port to connect to. <address> should be one of:\n"
 "\n"
+);
+ puts(
 "          interface   i.e \"eth0\" to specify which interface's  IP\n"
 "                      address you want to use  (Unix only)\n"
 "\n"
 "          IP address  i.e \"192.168.10.1\" to specify exact IP num­\n"
 "                      ber\n"
 "          host name   i.e \"my.host.domain\" to specify machine\n"
 "\n"
-);
- puts(
 "          -           (any single-letter string) to make it  pick\n"
 "                      the machine's default\n"
 "\n"
-"     If  this option is used serveral times, the last one will be\n"
+"     If  this  option is used several times, the last one will be\n"
 "     used.\n"
 "\n"
+);
+ puts(
 "     -q   If used as the first parameter on the command line, the\n"
 "          $HOME/.curlrc  file will not be read and used as a con­\n"
 "          fig file.\n"
 "\n"
 "     -Q/--quote <comand>\n"
 "          (FTP) Send an  arbitrary  command  to  the  remote  FTP\n"
 "          server,  by  using the QUOTE command of the server. Not\n"
-);
- puts(
 "          all servers support this command, and the set of  QUOTE\n"
 "          commands  are  server specific! Quote commands are sent\n"
+);
+ puts(
 "          BEFORE the transfer is taking place. To  make  commands\n"
 "          take  place  after  a  successful transfer, prefix them\n"
 "          with a dash '-'. You may specify any amount of commands\n"
 "          to  be run before and after the transfer. If the server\n"
 "          returns failure for one of  the  commands,  the  entire\n"
 "          operation will be aborted.\n"
 "\n"
-);
- puts(
 "          This option can be used multiple times.\n"
 "\n"
 "     --random-file <file>\n"
+);
+ puts(
 "          (HTTPS)  Specify  the path name to file containing what\n"
 "          will be considered as random data. The data is used  to\n"
 "          seed  the  random engine for SSL connections.  See also\n"
 "          the --edg-file option.\n"
 "\n"
 "     -r/--range <range>\n"
 "          (HTTP/FTP) Retrieve a byte range (i.e a  partial  docu­\n"
 "          ment)  from  a  HTTP/1.1  or  FTP server. Ranges can be\n"
-);
- puts(
 "          specified in a number of ways.\n"
 "\n"
 "          0-499     specifies the first 500 bytes\n"
 "\n"
+);
+ puts(
 "          500-999   specifies the second 500 bytes\n"
 "\n"
 "          -500      specifies the last 500 bytes\n"
 "\n"
 "          9500      specifies the bytes from offset 9500 and for­\n"
 "                    ward\n"
