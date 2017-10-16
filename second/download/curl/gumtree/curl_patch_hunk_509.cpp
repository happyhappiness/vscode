  fputs(
 "              \"certificate\"  file that is the private key and the private cer-\n"
 "              tificate concatenated! See --cert  and  --key  to  specify  them\n"
 "              independently.\n"
 "\n"
 "              If  curl  is  built against the NSS SSL library then this option\n"
-"              tells curl the nickname of the certificate to use within the NSS\n"
-"              database  defined  by  the  environment  variable SSL_DIR (or by\n"
+"              can tell curl the nickname of the certificate to use within  the\n"
+"              NSS  database defined by the environment variable SSL_DIR (or by\n"
 , stdout);
  fputs(
 "              default /etc/pki/nssdb). If the NSS  PEM  PKCS#11  module  (lib-\n"
-"              nsspem.so) is available then PEM files may be loaded.\n"
+"              nsspem.so)  is  available  then  PEM files may be loaded. If you\n"
+"              want to use a file from the current directory, please precede it\n"
+"              with \"./\" prefix, in order to avoid confusion with a nickname.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --cert-type <type>\n"
 "              (SSL)  Tells curl what certificate type the provided certificate\n"
+, stdout);
+ fputs(
 "              is in. PEM, DER and ENG are recognized types.  If not specified,\n"
 "              PEM is assumed.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --cacert <CA certificate>\n"
 "              (SSL) Tells curl to use the specified certificate file to verify\n"
 "              the peer. The file may contain  multiple  CA  certificates.  The\n"
 "              certificate(s)  must be in PEM format. Normally curl is built to\n"
+, stdout);
+ fputs(
 "              use a default file for this, so this option is typically used to\n"
 "              alter that default file.\n"
 "\n"
-, stdout);
- fputs(
 "              curl  recognizes the environment variable named 'CURL_CA_BUNDLE'\n"
 "              if it is set, and uses the given path as a path  to  a  CA  cert\n"
 "              bundle. This option overrides that variable.\n"
 "\n"
 "              The  windows  version  of  curl will automatically look for a CA\n"
 "              certs file named 'curl-ca-bundle.crt', either in the same direc-\n"
+, stdout);
+ fputs(
 "              tory as curl.exe, or in the Current Working Directory, or in any\n"
 "              folder along your PATH.\n"
 "\n"
-, stdout);
- fputs(
 "              If curl is built against the NSS SSL library  then  this  option\n"
 "              tells  curl the nickname of the CA certificate to use within the\n"
 "              NSS database defined by the environment variable SSL_DIR (or  by\n"
 "              default  /etc/pki/nssdb).   If  the NSS PEM PKCS#11 module (lib-\n"
+, stdout);
+ fputs(
 "              nsspem.so) is available then PEM files may be loaded.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       --capath <CA certificate directory>\n"
 "              (SSL) Tells curl to use the specified certificate  directory  to\n"
-"              verify the peer. The certificates must be in PEM format, and the\n"
-"              directory must have been processed using  the  c_rehash  utility\n"
-"              supplied  with  openssl.  Using  --capath can allow curl to make\n"
-"              SSL-connections much more efficiently than using --cacert if the\n"
-"              --cacert file contains many CA certificates.\n"
-"\n"
+"              verify  the peer. The certificates must be in PEM format, and if\n"
+"              curl is built against OpenSSL, the directory must have been pro-\n"
 , stdout);
  fputs(
+"              cessed  using  the c_rehash utility supplied with OpenSSL. Using\n"
+"              --capath can allow OpenSSL-powered curl to make  SSL-connections\n"
+"              much  more  efficiently than using --cacert if the --cacert file\n"
+"              contains many CA certificates.\n"
+"\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -f/--fail\n"
-"              (HTTP)  Fail  silently (no output at all) on server errors. This\n"
-"              is mostly done to better enable scripts etc to better deal  with\n"
-"              failed  attempts.  In  normal  cases when a HTTP server fails to\n"
-"              deliver a document, it  returns  an  HTML  document  stating  so\n"
-"              (which  often  also describes why and more). This flag will pre-\n"
+"              (HTTP) Fail silently (no output at all) on server  errors.  This\n"
 , stdout);
  fputs(
+"              is  mostly done to better enable scripts etc to better deal with\n"
+"              failed attempts. In normal cases when a  HTTP  server  fails  to\n"
+"              deliver  a  document,  it  returns  an  HTML document stating so\n"
+"              (which often also describes why and more). This flag  will  pre-\n"
 "              vent curl from outputting that and return error 22.\n"
 "\n"
-"              This method is not fail-safe and there are occasions where  non-\n"
-"              successful  response  codes  will  slip through, especially when\n"
+"              This  method is not fail-safe and there are occasions where non-\n"
+, stdout);
+ fputs(
+"              successful response codes will  slip  through,  especially  when\n"
 "              authentication is involved (response codes 401 and 407).\n"
 "\n"
 "       --ftp-account [data]\n"
 "              (FTP) When an FTP server asks for \"account data\" after user name\n"
-"              and  password has been provided, this data is sent off using the\n"
-, stdout);
- fputs(
+"              and password has been provided, this data is sent off using  the\n"
 "              ACCT command. (Added in 7.13.0)\n"
 "\n"
-"              If this option is used twice, the second will override the  pre-\n"
+"              If  this option is used twice, the second will override the pre-\n"
 "              vious use.\n"
 "\n"
+, stdout);
+ fputs(
 "       --ftp-create-dirs\n"
-"              (FTP/SFTP)  When  an  FTP or SFTP URL/operation uses a path that\n"
-"              doesn't currently exist on the server, the standard behavior  of\n"
+"              (FTP/SFTP) When an FTP or SFTP URL/operation uses  a  path  that\n"
+"              doesn't  currently exist on the server, the standard behavior of\n"
 "              curl is to fail. Using this option, curl will instead attempt to\n"
 "              create missing directories.\n"
 "\n"
 "       --ftp-method [method]\n"
+"              (FTP)  Control  what method curl should use to reach a file on a\n"
+"              FTP(S) server. The method argument should be one of the  follow-\n"
 , stdout);
  fputs(
-"              (FTP) Control what method curl should use to reach a file  on  a\n"
-"              FTP(S)  server. The method argument should be one of the follow-\n"
 "              ing alternatives:\n"
 "\n"
 "              multicwd\n"
-"                     curl does a single CWD operation for each  path  part  in\n"
-"                     the  given URL. For deep hierarchies this means very many\n"
-"                     commands. This is how RFC1738 says  it  should  be  done.\n"
-, stdout);
- fputs(
+"                     curl  does  a  single CWD operation for each path part in\n"
+"                     the given URL. For deep hierarchies this means very  many\n"
+"                     commands.  This  is  how RFC 1738 says it should be done.\n"
 "                     This is the default but the slowest behavior.\n"
 "\n"
-"              nocwd  curl  does  no  CWD at all. curl will do SIZE, RETR, STOR\n"
+"              nocwd  curl does no CWD at all. curl will do  SIZE,  RETR,  STOR\n"
+, stdout);
+ fputs(
 "                     etc and give a full path to the server for all these com-\n"
 "                     mands. This is the fastest behavior.\n"
 "\n"
 "              singlecwd\n"
 "                     curl does one CWD with the full target directory and then\n"
-"                     operates on the file \"normally\"  (like  in  the  multicwd\n"
-, stdout);
- fputs(
-"                     case).  This  is  somewhat  more standards compliant than\n"
+"                     operates  on  the  file  \"normally\" (like in the multicwd\n"
+"                     case). This is somewhat  more  standards  compliant  than\n"
 "                     'nocwd' but without the full penalty of 'multicwd'.\n"
 "       (Added in 7.15.1)\n"
 "\n"
+, stdout);
+ fputs(
 "       --ftp-pasv\n"
-"              (FTP) Use passive mode for the data conection.  Passive  is  the\n"
-"              internal  default behavior, but using this option can be used to\n"
+"              (FTP)  Use  passive mode for the data connection. Passive is the\n"
+"              internal default behavior, but using this option can be used  to\n"
 "              override a previous -P/-ftp-port option. (Added in 7.11.0)\n"
 "\n"
+"              If  this option is used several times, the following occurrences\n"
+"              make no difference. Undoing an  enforced  passive  really  isn't\n"
+"              doable  but  you must then instead enforce the correct -P/--ftp-\n"
 , stdout);
  fputs(
-"              If this option is used several times, the following  occurrences\n"
-"              make  no  difference.  Undoing  an enforced passive really isn't\n"
-"              doable but you must then instead enforce the  correct  -P/--ftp-\n"
 "              port again.\n"
 "\n"
 "              Passive mode means that curl will try the EPSV command first and\n"
 "              then PASV, unless --disable-epsv is used.\n"
 "\n"
 "       --ftp-alternative-to-user <command>\n"
+"              (FTP)  If  authenticating with the USER and PASS commands fails,\n"
+"              send this  command.   When  connecting  to  Tumbleweed's  Secure\n"
+"              Transport  server  over  FTPS  using a client certificate, using\n"
 , stdout);
  fputs(
-"              (FTP) If authenticating with the USER and PASS  commands  fails,\n"
-"              send  this  command.   When  connecting  to  Tumbleweed's Secure\n"
-"              Transport server over FTPS using  a  client  certificate,  using\n"
-"              \"SITE  AUTH\"  will tell the server to retrieve the username from\n"
+"              \"SITE AUTH\" will tell the server to retrieve the  username  from\n"
 "              the certificate. (Added in 7.15.5)\n"
 "\n"
 "       --ftp-skip-pasv-ip\n"
 "              (FTP) Tell curl to not use the IP address the server suggests in\n"
-, stdout);
- fputs(
-"              its  response to curl's PASV command when curl connects the data\n"
-"              connection. Instead curl will re-use  the  same  IP  address  it\n"
+"              its response to curl's PASV command when curl connects the  data\n"
+"              connection.  Instead  curl  will  re-use  the same IP address it\n"
 "              already uses for the control connection. (Added in 7.14.2)\n"
 "\n"
-"              This  option has no effect if PORT, EPRT or EPSV is used instead\n"
+, stdout);
+ fputs(
+"              This option has no effect if PORT, EPRT or EPSV is used  instead\n"
 "              of PASV.\n"
 "\n"
 "       --ftp-pret\n"
-"              (FTP) Tell curl to send a PRET command before PASV  (and  EPSV).\n"
-, stdout);
- fputs(
-"              Certain  FTP  servers,  mainly drftpd, require this non-standard\n"
-"              command for directory listings as well as up  and  downloads  in\n"
+"              (FTP)  Tell  curl to send a PRET command before PASV (and EPSV).\n"
+"              Certain FTP servers, mainly drftpd,  require  this  non-standard\n"
+"              command  for  directory  listings as well as up and downloads in\n"
 "              PASV mode.  (Added in 7.20.x)\n"
 "\n"
-"       --ssl  (FTP,  POP3,  IMAP, SMTP) Try to use SSL/TLS for the connection.\n"
-"              Reverts to a non-secure connection if the server doesn't support\n"
-"              SSL/TLS.   See also --ftp-ssl-control and --ssl-reqd for differ-\n"
+"       --ssl  (FTP, POP3, IMAP, SMTP) Try to use SSL/TLS for  the  connection.\n"
 , stdout);
  fputs(
+"              Reverts to a non-secure connection if the server doesn't support\n"
+"              SSL/TLS.  See also --ftp-ssl-control and --ssl-reqd for  differ-\n"
 "              ent levels of encryption required. (Added in 7.20.0)\n"
 "\n"
-"              This option was formerly known as --ftp-ssl  (Added  in  7.11.0)\n"
-"              and  that can still be used but will be removed in a future ver-\n"
+"              This  option  was  formerly known as --ftp-ssl (Added in 7.11.0)\n"
+"              and that can still be used but will be removed in a future  ver-\n"
 "              sion.\n"
 "\n"
 "       --ftp-ssl-control\n"
-"              (FTP) Require SSL/TLS for the FTP  login,  clear  for  transfer.\n"
-"              Allows  secure  authentication, but non-encrypted data transfers\n"
 , stdout);
  fputs(
-"              for efficiency.  Fails the transfer if the server  doesn't  sup-\n"
+"              (FTP)  Require  SSL/TLS  for  the FTP login, clear for transfer.\n"
+"              Allows secure authentication, but non-encrypted  data  transfers\n"
+"              for  efficiency.   Fails the transfer if the server doesn't sup-\n"
 "              port SSL/TLS.  (Added in 7.16.0)\n"
 "\n"
 "       --ssl-reqd\n"
-"              (FTP,  POP3,  IMAP,  SMTP)  Require  SSL/TLS for the connection.\n"
+"              (FTP, POP3, IMAP, SMTP)  Require  SSL/TLS  for  the  connection.\n"
 "              Terminates the connection if the server doesn't support SSL/TLS.\n"
 "              (Added in 7.20.0)\n"
 "\n"
-"              This  option  was  formerly  known  as  --ftp-ssl-reqd (added in\n"
-"              7.15.5) and that can still be used but  will  be  removed  in  a\n"
 , stdout);
  fputs(
+"              This option was  formerly  known  as  --ftp-ssl-reqd  (added  in\n"
+"              7.15.5)  and  that  can  still  be used but will be removed in a\n"
 "              future version.\n"
 "\n"
 "       --ftp-ssl-ccc\n"
-"              (FTP)  Use  CCC  (Clear  Command Channel) Shuts down the SSL/TLS\n"
+"              (FTP) Use CCC (Clear Command Channel)  Shuts  down  the  SSL/TLS\n"
 "              layer after authenticating. The rest of the control channel com-\n"
-"              munication  will be unencrypted. This allows NAT routers to fol-\n"
+"              munication will be unencrypted. This allows NAT routers to  fol-\n"
+, stdout);
+ fputs(
 "              low the FTP transaction. The default mode is passive. See --ftp-\n"
 "              ssl-ccc-mode for other modes.  (Added in 7.16.1)\n"
 "\n"
 "       --ftp-ssl-ccc-mode [active/passive]\n"
+"              (FTP) Use CCC (Clear Command Channel) Sets  the  CCC  mode.  The\n"
+"              passive  mode  will  not initiate the shutdown, but instead wait\n"
+"              for the server to do it, and will not reply to the shutdown from\n"
 , stdout);
  fputs(
-"              (FTP)  Use  CCC  (Clear  Command Channel) Sets the CCC mode. The\n"
-"              passive mode will not initiate the shutdown,  but  instead  wait\n"
-"              for the server to do it, and will not reply to the shutdown from\n"
 "              the server. The active mode initiates the shutdown and waits for\n"
 "              a reply from the server.  (Added in 7.16.2)\n"
 "\n"
 "       -F/--form <name=content>\n"
-"              (HTTP)  This  lets curl emulate a filled-in form in which a user\n"
+"              (HTTP) This lets curl emulate a filled-in form in which  a  user\n"
+"              has  pressed  the  submit  button. This causes curl to POST data\n"
+"              using the  Content-Type  multipart/form-data  according  to  RFC\n"
+"              2388.  This  enables uploading of binary files etc. To force the\n"
 , stdout);
  fputs(
-"              has pressed the submit button. This causes  curl  to  POST  data\n"
-"              using the Content-Type multipart/form-data according to RFC2388.\n"
-"              This enables uploading of binary files etc. To force  the  'con-\n"
-"              tent' part to be a file, prefix the file name with an @ sign. To\n"
-"              just get the content part from a file, prefix the file name with\n"
-"              the  symbol  <.  The  difference  between @ and < is then that @\n"
+"              'content' part to be a file, prefix the  file  name  with  an  @\n"
+"              sign.  To just get the content part from a file, prefix the file\n"
+"              name with the symbol <. The difference between @ and <  is  then\n"
+"              that  @  makes a file get attached in the post as a file upload,\n"
+"              while the < makes a text field and just  get  the  contents  for\n"
+"              that text field from a file.\n"
+"\n"
 , stdout);
  fputs(
-"              makes a file get attached in the post as a  file  upload,  while\n"
-"              the < makes a text field and just get the contents for that text\n"
-"              field from a file.\n"
-"\n"
-"              Example, to send your password file to the server, where  'pass-\n"
+"              Example,  to send your password file to the server, where 'pass-\n"
 "              word' is the name of the form-field to which /etc/passwd will be\n"
 "              the input:\n"
 "\n"
 "              curl -F password=@/etc/passwd www.mypasswords.com\n"
 "\n"
-, stdout);
- fputs(
-"              To read the file's content from stdin instead of a file,  use  -\n"
-"              where  the  file name should've been. This goes for both @ and <\n"
-"              constructs.\n"
+"              To read content from stdin instead of a file, use - as the file-\n"
+"              name. This goes for both @ and < constructs.\n"
 "\n"
 "              You can also  tell  curl  what  Content-Type  to  use  by  using\n"
+, stdout);
+ fputs(
 "              'type=', in a manner similar to:\n"
 "\n"
 "              curl -F \"web=@index.html;type=text/html\" url.com\n"
 "\n"
 "              or\n"
 "\n"
 "              curl -F \"name=daniel;type=text/foo\" url.com\n"
 "\n"
-, stdout);
- fputs(
 "              You  can  also explicitly change the name field of a file upload\n"
 "              part by setting filename=, like this:\n"
 "\n"
 "              curl -F \"file=@localfile;filename=nameinpost\" url.com\n"
 "\n"
 "              See further examples and details in the MANUAL.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option can be used multiple times.\n"
 "\n"
 "       --form-string <name=string>\n"
 "              (HTTP) Similar to --form except that the value  string  for  the\n"
-, stdout);
- fputs(
 "              named  parameter  is used literally. Leading '@' and '<' charac-\n"
 "              ters, and the ';type=' string in the value have no special mean-\n"
 "              ing. Use this in preference to --form if there's any possibility\n"
 "              that the string value may accidentally trigger the  '@'  or  '<'\n"
+, stdout);
+ fputs(
 "              features of --form.\n"
 "\n"
 "       -g/--globoff\n"
 "              This option switches off the \"URL globbing parser\". When you set\n"
-, stdout);
- fputs(
 "              this option, you can specify URLs that contain the letters  {}[]\n"
 "              without  having them being interpreted by curl itself. Note that\n"
 "              these letters are not normal legal URL contents but they  should\n"
 "              be encoded according to the URI standard.\n"
 "\n"
 "       -G/--get\n"
-"              When  used,  this  option  will  make  all  data  specified with\n"
-"              -d/--data or --data-binary to be used  in  a  HTTP  GET  request\n"
 , stdout);
  fputs(
+"              When  used,  this  option  will  make  all  data  specified with\n"
+"              -d/--data or --data-binary to be used  in  a  HTTP  GET  request\n"
 "              instead  of  the  POST request that otherwise would be used. The\n"
 "              data will be appended to the URL with a '?' separator.\n"
 "\n"
 "              If used in combination with -I, the POST data  will  instead  be\n"
 "              appended to the URL with a HEAD request.\n"
 "\n"
-"              If  this option is used several times, the following occurrences\n"
-"              make no difference. This is because undoing a GET  doesn't  make\n"
 , stdout);
  fputs(
+"              If  this option is used several times, the following occurrences\n"
+"              make no difference. This is because undoing a GET  doesn't  make\n"
 "              sense,  but  you  should  then  instead  enforce the alternative\n"
 "              method you prefer.\n"
 "\n"
 "       -h/--help\n"
 "              Usage help.\n"
 "\n"
 "       -H/--header <header>\n"
 "              (HTTP) Extra header to use when getting  a  web  page.  You  may\n"
-"              specify any number of extra headers. Note that if you should add\n"
-"              a custom header that has the same name as one  of  the  internal\n"
 , stdout);
  fputs(
+"              specify any number of extra headers. Note that if you should add\n"
+"              a custom header that has the same name as one  of  the  internal\n"
 "              ones  curl  would  use,  your externally set header will be used\n"
 "              instead of the internal one. This allows you to make even trick-\n"
 "              ier  stuff  than  curl would normally do. You should not replace\n"
 "              internally set  headers  without  knowing  perfectly  well  what\n"
+, stdout);
+ fputs(
 "              you're  doing. Remove an internal header by giving a replacement\n"
 "              without content on the right  side  of  the  colon,  as  in:  -H\n"
 "              \"Host:\".\n"
 "\n"
-, stdout);
- fputs(
 "              curl  will  make  sure  that each header you add/replace is sent\n"
 "              with the proper end-of-line marker, you should thus not add that\n"
 "              as a part of the header content: do not add newlines or carriage\n"
 "              returns, they will only mess things up for you.\n"
 "\n"
+, stdout);
+ fputs(
 "              See also the -A/--user-agent and -e/--referer options.\n"
 "\n"
 "              This option can be used  multiple  times  to  add/replace/remove\n"
 "              multiple headers.\n"
 "\n"
-, stdout);
- fputs(
 "       --hostpubmd5 <md5>\n"
 "              Pass  a  string  containing  32  hexadecimal  digits. The string\n"
 "              should be the 128 bit MD5 checksum of the remote  host's  public\n"
 "              key,  curl  will  refuse the connection with the host unless the\n"
+, stdout);
+ fputs(
 "              md5sums match. This option is only for SCP and  SFTP  transfers.\n"
 "              (Added in 7.17.1)\n"
 "\n"
 "       --ignore-content-length\n"
 "              (HTTP)  Ignore  the  Content-Length header. This is particularly\n"
-, stdout);
- fputs(
 "              useful for servers running Apache 1.x, which will report  incor-\n"
 "              rect Content-Length for files larger than 2 gigabytes.\n"
 "\n"
 "       -i/--include\n"
 "              (HTTP)  Include  the  HTTP-header in the output. The HTTP-header\n"
+, stdout);
+ fputs(
 "              includes things like server-name, date of  the  document,  HTTP-\n"
 "              version and more...\n"
 "\n"
 "       --interface <name>\n"
 "              Perform  an operation using a specified interface. You can enter\n"
-, stdout);
- fputs(
 "              interface name, IP address or host name. An example  could  look\n"
 "              like:\n"
 "\n"
 "               curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -I/--head\n"
+, stdout);
+ fputs(
 "              (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature\n"
 "              the command HEAD which this uses to get nothing but  the  header\n"
 "              of  a  document.  When used on a FTP or FILE file, curl displays\n"
-, stdout);
- fputs(
 "              the file size and last modification time only.\n"
 "\n"
 "       -j/--junk-session-cookies\n"
 "              (HTTP) When curl is told to read cookies from a given file, this\n"
 "              option  will  make  it  discard all \"session cookies\". This will\n"
+, stdout);
+ fputs(
 "              basically have the same effect as if a new session  is  started.\n"
 "              Typical  browsers  always  discard  session cookies when they're\n"
 "              closed down.\n"
 "\n"
 "       -J/--remote-header-name\n"
-, stdout);
- fputs(
 "              (HTTP) This option tells the -O/--remote-name option to use  the\n"
 "              server-specified   Content-Disposition   filename   instead   of\n"
 "              extracting a filename from the URL.\n"
 "\n"
 "       -k/--insecure\n"
+, stdout);
+ fputs(
 "              (SSL) This option explicitly allows curl to  perform  \"insecure\"\n"
 "              SSL connections and transfers. All SSL connections are attempted\n"
 "              to be made secure by using the CA certificate  bundle  installed\n"
-, stdout);
- fputs(
 "              by  default.  This  makes  all connections considered \"insecure\"\n"
 "              fail unless -k/--insecure is used.\n"
 "\n"
 "              See    this    online    resource    for    further     details:\n"
 "              http://curl.haxx.se/docs/sslcerts.html\n"
+, stdout);
+ fputs(
 "\n"
 "       --keepalive-time <seconds>\n"
 "              This  option  sets  the  time  a connection needs to remain idle\n"
 "              before sending keepalive probes and the time between  individual\n"
-, stdout);
- fputs(
 "              keepalive probes. It is currently effective on operating systems\n"
 "              offering  the  TCP_KEEPIDLE  and  TCP_KEEPINTVL  socket  options\n"
 "              (meaning  Linux, recent AIX, HP-UX and more). This option has no\n"
 "              effect if --no-keepalive is used. (Added in 7.18.0)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used multiple times, the last occurrence  sets\n"
 "              the amount.\n"
 "       --key <key>\n"
-, stdout);
- fputs(
 "              (SSL/SSH) Private key file name. Allows you to provide your pri-\n"
 "              vate key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --key-type <type>\n"
 "              (SSL) Private key file type. Specify which type your --key  pro-\n"
+, stdout);
+ fputs(
 "              vided  private  key  is. DER, PEM, and ENG are supported. If not\n"
 "              specified, PEM is assumed.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --krb <level>\n"
 "              (FTP) Enable Kerberos authentication and use. The level must  be\n"
 "              entered and should be one of 'clear', 'safe', 'confidential', or\n"
 "              'private'. Should you use a level that  is  not  one  of  these,\n"
+, stdout);
+ fputs(
 "              'private' will instead be used.\n"
 "\n"
 "              This  option  requires  a library built with kerberos4 or GSSAPI\n"
-, stdout);
- fputs(
 "              (GSS-Negotiate) support. This is not very common. Use  -V/--ver-\n"
 "              sion to see if your curl supports it.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -K/--config <config file>\n"
 "              Specify  which config file to read curl arguments from. The con-\n"
-"              fig file is a text file in which command line arguments  can  be\n"
-"              written  which  then will be used as if they were written on the\n"
 , stdout);
  fputs(
+"              fig file is a text file in which command line arguments  can  be\n"
+"              written  which  then will be used as if they were written on the\n"
 "              actual command line. Options and their parameters must be speci-\n"
 "              fied  on  the  same  config  file line, separated by whitespace,\n"
 "              colon, the equals sign or any combination thereof (however,  the\n"
 "              preferred  separator is the equals sign). If the parameter is to\n"
-"              contain  whitespace,  the  parameter  must  be  enclosed  within\n"
-"              quotes. Within double quotes, the following escape sequences are\n"
 , stdout);
  fputs(
+"              contain  whitespace,  the  parameter  must  be  enclosed  within\n"
+"              quotes. Within double quotes, the following escape sequences are\n"
 "              available: \\\\, \\\", \\t, \\n, \\r and \\v. A backslash preceding  any\n"
 "              other letter is ignored. If the first column of a config line is\n"
 "              a '#' character, the rest of the line will be treated as a  com-\n"
 "              ment.  Only  write  one  option  per physical line in the config\n"
 "              file.\n"
 "\n"
+, stdout);
+ fputs(
 "              Specify the filename to -K/--config as '-' to make curl read the\n"
 "              file from stdin.\n"
 "\n"
-, stdout);
- fputs(
 "              Note  that  to  be able to specify a URL in the config file, you\n"
 "              need to specify it using the --url option,  and  not  by  simply\n"
 "              writing  the  URL  on its own line. So, it could look similar to\n"
 "              this:\n"
 "\n"
 "              url = \"http://curl.haxx.se/docs/\"\n"
 "\n"
 "              Long option names can optionally be given  in  the  config  file\n"
-"              without the initial double dashes.\n"
-"\n"
 , stdout);
  fputs(
+"              without the initial double dashes.\n"
+"\n"
 "              When curl is invoked, it always (unless -q is used) checks for a\n"
 "              default config file and uses it if  found.  The  default  config\n"
 "              file is checked for in the following places in this order:\n"
 "\n"
 "              1)  curl  tries  to find the \"home dir\": It first checks for the\n"
 "              CURL_HOME and then the HOME environment variables. Failing that,\n"
-"              it  uses getpwuid() on UNIX-like systems (which returns the home\n"
 , stdout);
  fputs(
+"              it  uses getpwuid() on UNIX-like systems (which returns the home\n"
 "              dir given the current user in your system). On Windows, it  then\n"
 "              checks for the APPDATA variable, or as a last resort the '%USER-\n"
 "              PROFILE%\\Application Data'.\n"
 "\n"
 "              2) On windows, if there is no _curlrc file in the home  dir,  it\n"
 "              checks for one in the same dir the curl executable is placed. On\n"
+, stdout);
+ fputs(
 "              UNIX-like systems, it will simply try to load .curlrc  from  the\n"
 "              determined home dir.\n"
 "\n"
-, stdout);
- fputs(
 "              # --- Example file ---\n"
 "              # this is a comment\n"
 "              url = \"curl.haxx.se\"\n"
 "              output = \"curlhere.html\"\n"
 "              user-agent = \"superagent/1.0\"\n"
 "\n"
 "              # and fetch another URL too\n"
 "              url = \"curl.haxx.se/docs/manpage.html\"\n"
 "              -O\n"
 "              referer = \"http://nowhereatall.com/\"\n"
+, stdout);
+ fputs(
 "              # --- End of example file ---\n"
 "\n"
 "              This  option  can be used multiple times to load multiple config\n"
 "              files.\n"
 "\n"
-, stdout);
- fputs(
 "       --libcurl <file>\n"
 "              Append this option to any ordinary curl command  line,  and  you\n"
 "              will  get  a  libcurl-using source code written to the file that\n"
 "              does the equivalent of what your command-line operation does!\n"
 "\n"
 "              NOTE: this does not properly support -F and the sending of  mul-\n"
+, stdout);
+ fputs(
 "              tipart  formposts,  so in those cases the output program will be\n"
 "              missing necessary calls to curl_formadd(3), and possibly more.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last given  file  name\n"
 "              will be used. (Added in 7.16.1)\n"
 "\n"
 "       --limit-rate <speed>\n"
 "              Specify  the  maximum  transfer  rate you want curl to use. This\n"
 "              feature is useful if you have a limited pipe and you'd like your\n"
+, stdout);
+ fputs(
 "              transfer not to use your entire bandwidth.\n"
 "\n"
 "              The  given speed is measured in bytes/second, unless a suffix is\n"
-, stdout);
- fputs(
 "              appended.  Appending 'k' or 'K' will count the number  as  kilo-\n"
 "              bytes,  'm'  or M' makes it megabytes, while 'g' or 'G' makes it\n"
 "              gigabytes. Examples: 200K, 3m and 1G.\n"
 "\n"
 "              The given rate is the average speed counted  during  the  entire\n"
-"              transfer. It means that curl might use higher transfer speeds in\n"
-"              short bursts, but over time it uses no more than the given rate.\n"
 , stdout);
  fputs(
+"              transfer. It means that curl might use higher transfer speeds in\n"
+"              short bursts, but over time it uses no more than the given rate.\n"
 "              If you also use the -Y/--speed-limit option,  that  option  will\n"
 "              take precedence and might cripple the rate-limiting slightly, to\n"
 "              help keeping the speed-limit logic working.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -l/--list-only\n"
-"              (FTP) When listing an FTP directory, this switch forces a  name-\n"
-"              only  view.   Especially useful if you want to machine-parse the\n"
 , stdout);
  fputs(
+"              (FTP) When listing an FTP directory, this switch forces a  name-\n"
+"              only  view.   Especially useful if you want to machine-parse the\n"
 "              contents of an FTP directory since  the  normal  directory  view\n"
 "              doesn't use a standard look or format.\n"
 "\n"
 "              This  option  causes  an  FTP NLST command to be sent.  Some FTP\n"
 "              servers list only files in their response to NLST; they  do  not\n"
+, stdout);
+ fputs(
 "              include subdirectories and symbolic links.\n"
 "\n"
 "       --local-port <num>[-num]\n"
 "              Set a preferred number or range of local port numbers to use for\n"
-, stdout);
- fputs(
 "              the connection(s).  Note that  port  numbers  by  nature  are  a\n"
 "              scarce resource that will be busy at times so setting this range\n"
 "              to something too narrow might cause unnecessary connection setup\n"
 "              failures. (Added in 7.15.2)\n"
 "\n"
 "       -L/--location\n"
-"              (HTTP/HTTPS)  If  the server reports that the requested page has\n"
-"              moved to a different location (indicated with a Location: header\n"
 , stdout);
  fputs(
+"              (HTTP/HTTPS)  If  the server reports that the requested page has\n"
+"              moved to a different location (indicated with a Location: header\n"
 "              and  a  3XX  response code), this option will make curl redo the\n"
 "              request on the new place. If used together with -i/--include  or\n"
 "              -I/--head,  headers from all requested pages will be shown. When\n"
 "              authentication is used, curl only sends its credentials  to  the\n"
-"              initial  host.  If a redirect takes curl to a different host, it\n"
-"              won't be able to intercept the user+password. See  also  --loca-\n"
 , stdout);
  fputs(
+"              initial  host.  If a redirect takes curl to a different host, it\n"
+"              won't be able to intercept the user+password. See  also  --loca-\n"
 "              tion-trusted  on how to change this. You can limit the amount of\n"
 "              redirects to follow by using the --max-redirs option.\n"
 "\n"
 "              When curl follows a redirect and the request is not a plain  GET\n"
 "              (for example POST or PUT), it will do the following request with\n"
-"              a GET if the HTTP response was 301, 302, or 303. If the response\n"
-"              code  was  any  other  3xx code, curl will re-send the following\n"
 , stdout);
  fputs(
+"              a GET if the HTTP response was 301, 302, or 303. If the response\n"
+"              code  was  any  other  3xx code, curl will re-send the following\n"
 "              request using the same unmodified method.\n"
 "\n"
 "       --location-trusted\n"
 "              (HTTP/HTTPS) Like -L/--location, but will allow sending the name\n"
 "              +  password to all hosts that the site may redirect to. This may\n"
 "              or may not introduce a security breach if the site redirects you\n"
+, stdout);
+ fputs(
 "              to  a  site to which you'll send your authentication info (which\n"
 "              is plaintext in the case of HTTP Basic authentication).\n"
 "\n"
 "       --mail-rcpt <address>\n"
-, stdout);
- fputs(
 "              (SMTP) Specify a single address that the given mail  should  get\n"
 "              sent  to. This option can be used multiple times to specify many\n"
 "              recipients.\n"
 "\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "       --mail-from <address>\n"
+, stdout);
+ fputs(
 "              (SMTP) Specify a single address that the given mail  should  get\n"
 "              sent from.\n"
 "\n"
 "              (Added in 7.20.0)\n"
 "\n"
 "       --max-filesize <bytes>\n"
 "              Specify  the  maximum  size (in bytes) of a file to download. If\n"
-, stdout);
- fputs(
 "              the file requested is larger than this value, the transfer  will\n"
 "              not start and curl will return with exit code 63.\n"
 "\n"
 "              NOTE:  The  file size is not always known prior to download, and\n"
+, stdout);
+ fputs(
 "              for such files this option has no effect even if the file trans-\n"
 "              fer  ends  up  being larger than this given limit. This concerns\n"
 "              both FTP and HTTP transfers.\n"
 "\n"
 "       -m/--max-time <seconds>\n"
-, stdout);
- fputs(
 "              Maximum time in seconds that you allow the  whole  operation  to\n"
 "              take.   This is useful for preventing your batch jobs from hang-\n"
 "              ing for hours due to slow networks or  links  going  down.   See\n"
+, stdout);
+ fputs(
 "              also the --connect-timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -M/--manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
 "       -n/--netrc\n"
-, stdout);
- fputs(
 "              Makes  curl  scan  the  .netrc  (_netrc  on Windows) file in the\n"
 "              user's home directory for login name and password. This is typi-\n"
 "              cally  used for FTP on UNIX. If used with HTTP, curl will enable\n"
+, stdout);
+ fputs(
 "              user authentication. See netrc(4) or ftp(1) for details  on  the\n"
 "              file  format.  Curl  will not complain if that file doesn't have\n"
 "              the right permissions (it should not be either world- or  group-\n"
-, stdout);
- fputs(
 "              readable).  The  environment variable \"HOME\" is used to find the\n"
 "              home directory.\n"
 "\n"
 "              A quick and very simple example of how  to  setup  a  .netrc  to\n"
+, stdout);
+ fputs(
 "              allow  curl to FTP to the machine host.domain.com with user name\n"
 "              'myself' and password 'secret' should look similar to:\n"
 "\n"
 "              machine host.domain.com login myself password secret\n"
 "\n"
 "       --netrc-optional\n"
-, stdout);
- fputs(
 "              Very similar to --netrc, but this option makes the .netrc  usage\n"
 "              optional and not mandatory as the --netrc option does.\n"
 "\n"
 "       --negotiate\n"
 "              (HTTP)  Enables  GSS-Negotiate authentication. The GSS-Negotiate\n"
+, stdout);
+ fputs(
 "              method was designed by Microsoft and is used in their web appli-\n"
 "              cations.  It  is  primarily  meant  as  a  support for Kerberos5\n"
 "              authentication but may be also used along with another authenti-\n"
-, stdout);
- fputs(
 "              cation method. For more information see IETF draft draft-brezak-\n"
 "              spnego-http-04.txt.\n"
 "\n"
 "              If you want to enable Negotiate for your  proxy  authentication,\n"
 "              then use --proxy-negotiate.\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  requires a library built with GSSAPI support. This\n"
 "              is not very common. Use -V/--version to see if your version sup-\n"
 "              ports GSS-Negotiate.\n"
 "\n"
-, stdout);
- fputs(
 "              When  using  this option, you must also provide a fake -u/--user\n"
 "              option to activate the authentication code properly.  Sending  a\n"
 "              '-u  :'  is  enough  as  the  user name and password from the -u\n"
 "              option aren't actually used.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the following  occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -N/--no-buffer\n"
 "              Disables the buffering of the output stream. In normal work sit-\n"
-, stdout);
- fputs(
 "              uations, curl will use a standard buffered  output  stream  that\n"
 "              will have the effect that it will output the data in chunks, not\n"
 "              necessarily exactly when the data arrives.   Using  this  option\n"
 "              will disable that buffering.\n"
 "\n"
+, stdout);
+ fputs(
 "              Note  that  this  is the negated option name documented. You can\n"
 "              thus use --buffer to enforce the buffering.\n"
 "\n"
 "       --no-keepalive\n"
-, stdout);
- fputs(
 "              Disables the use of keepalive messages on the TCP connection, as\n"
 "              by default curl enables them.\n"
 "\n"
 "              Note  that  this  is the negated option name documented. You can\n"
 "              thus use --keepalive to enforce keepalive.\n"
 "\n"
 "       --no-sessionid\n"
-"              (SSL) Disable curl's use of SSL session-ID caching.  By  default\n"
-"              all  transfers are done using the cache. Note that while nothing\n"
 , stdout);
  fputs(
+"              (SSL) Disable curl's use of SSL session-ID caching.  By  default\n"
+"              all  transfers are done using the cache. Note that while nothing\n"
 "              should ever get hurt by attempting  to  reuse  SSL  session-IDs,\n"
 "              there seem to be broken SSL implementations in the wild that may\n"
 "              require you to disable this in order for you to succeed.  (Added\n"
 "              in 7.16.0)\n"
 "\n"
 "              Note  that  this  is the negated option name documented. You can\n"
+, stdout);
+ fputs(
 "              thus use --sessionid to enforce session-ID caching.\n"
 "\n"
 "       --noproxy <no-proxy-list>\n"
-, stdout);
- fputs(
 "              Comma-separated list of hosts which do not use a proxy,  if  one\n"
 "              is  specified.  The only wildcard is a single * character, which\n"
 "              matches all hosts, and effectively disables the proxy. Each name\n"
 "              in  this  list  is matched as either a domain which contains the\n"
 "              hostname, or the hostname itself. For example,  local.com  would\n"
-"              match   local.com,  local.com:80,  and  www.local.com,  but  not\n"
 , stdout);
  fputs(
+"              match   local.com,  local.com:80,  and  www.local.com,  but  not\n"
 "              www.notlocal.com.  (Added in 7.19.4).\n"
 "\n"
 "       --ntlm (HTTP) Enables  NTLM  authentication.  The  NTLM  authentication\n"
 "              method was designed by Microsoft and is used by IIS web servers.\n"
 "              It is a proprietary protocol, reverse-engineered by clever  peo-\n"
 "              ple and implemented in curl based on their efforts. This kind of\n"
-"              behavior should not be endorsed, you should  encourage  everyone\n"
 , stdout);
  fputs(
+"              behavior should not be endorsed, you should  encourage  everyone\n"
 "              who  uses  NTLM to switch to a public and documented authentica-\n"
 "              tion method instead, such as Digest.\n"
 "\n"
 "              If you want to enable NTLM for your proxy  authentication,  then\n"
 "              use --proxy-ntlm.\n"
 "\n"
 "              This  option  requires  a  library  built  with SSL support. Use\n"
 "              -V/--version to see if your curl supports NTLM.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the following  occurrences\n"
 "              make no difference.\n"
 "\n"
-, stdout);
- fputs(
 "       -o/--output <file>\n"
 "              Write output to <file> instead of stdout. If you are using {} or\n"
 "              [] to fetch multiple documents, you can use '#'  followed  by  a\n"
 "              number  in  the <file> specifier. That variable will be replaced\n"
 "              with the current string for the URL being fetched. Like in:\n"
 "\n"
+, stdout);
+ fputs(
 "                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
 "              or use several variables like:\n"
 "\n"
-, stdout);
- fputs(
 "                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
 "\n"
 "              You may use this option as many times as the number of URLs  you\n"
 "              have.\n"
 "\n"
 "              See  also  the --create-dirs option to create the local directo-\n"
 "              ries dynamically. Specifying the output as '-' (a  single  dash)\n"
 "              will force the output to be done to stdout.\n"
 "\n"
-"       -O/--remote-name\n"
-"              Write  output to a local file named like the remote file we get.\n"
 , stdout);
  fputs(
+"       -O/--remote-name\n"
+"              Write  output to a local file named like the remote file we get.\n"
 "              (Only the file part of the remote file is used, the path is  cut\n"
 "              off.)\n"
 "\n"
 "              The  remote  file  name  to use for saving is extracted from the\n"
 "              given URL, nothing else.\n"
 "\n"
 "              You may use this option as many times as the number of URLs  you\n"
 "              have.\n"
 "\n"
 "       --remote-name-all\n"
-"              This  option changes the default action for all given URLs to be\n"
 , stdout);
  fputs(
+"              This  option changes the default action for all given URLs to be\n"
 "              dealt with as if -O/--remote-name were used for each one. So  if\n"
 "              you want to disable that for a specific URL after --remote-name-\n"
 "              all has been used, you must  use  \"-o  -\"  or  --no-remote-name.\n"
 "              (Added in 7.19.0)\n"
 "\n"
 "       --pass <phrase>\n"
 "              (SSL/SSH) Passphrase for the private key\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --post301\n"
-, stdout);
- fputs(
 "              Tells  curl  to  respect  RFC  2616/10.3.2  and not convert POST\n"
 "              requests into GET requests when following a 301 redirection. The\n"
 "              non-RFC  behaviour  is  ubiquitous in web browsers, so curl does\n"
 "              the conversion by default to maintain  consistency.  However,  a\n"
 "              server  may  require  a POST to remain a POST after such a redi-\n"
-"              rection. This option is meaningful only when using -L/--location\n"
 , stdout);
  fputs(
+"              rection. This option is meaningful only when using -L/--location\n"
 "              (Added in 7.17.1)\n"
 "\n"
 "       --post302\n"
 "              Tells  curl  to  respect  RFC  2616/10.3.2  and not convert POST\n"
 "              requests into GET requests when following a 302 redirection. The\n"
 "              non-RFC  behaviour  is  ubiquitous in web browsers, so curl does\n"
 "              the conversion by default to maintain  consistency.  However,  a\n"
-"              server  may  require  a POST to remain a POST after such a redi-\n"
 , stdout);
  fputs(
+"              server  may  require  a POST to remain a POST after such a redi-\n"
 "              rection. This option is meaningful only when using -L/--location\n"
 "              (Added in 7.19.1)\n"
 "\n"
 "       --proto <protocols>\n"
 "              Tells   curl  to  use  the  listed  protocols  for  its  initial\n"
 "              retrieval. Protocols are evaluated left to right, are comma sep-\n"
 "              arated,  and  are each a protocol name or 'all', optionally pre-\n"
-"              fixed by zero or more modifiers. Available modifiers are:\n"
-"\n"
 , stdout);
  fputs(
+"              fixed by zero or more modifiers. Available modifiers are:\n"
+"\n"
 "              +  Permit this protocol in addition to protocols already permit-\n"
 "                 ted (this is the default if no modifier is used).\n"
 "\n"
 "              -  Deny  this  protocol,  removing it from the list of protocols\n"
 "                 already permitted.\n"
 "\n"
 "              =  Permit only this protocol (ignoring the list already  permit-\n"
 "                 ted),  though  subject  to  later  modification by subsequent\n"
-"                 entries in the comma separated list.\n"
-"\n"
 , stdout);
  fputs(
+"                 entries in the comma separated list.\n"
+"\n"
 "              For example:\n"
 "\n"
 "              --proto -ftps  uses the default protocols, but disables ftps\n"
 "\n"
 "              --proto -all,https,+http\n"
 "                             only enables http and https\n"
 "\n"
 "              --proto =http,https\n"
 "                             also only enables http and https\n"
 "\n"
 "              Unknown protocols produce a  warning.  This  allows  scripts  to\n"
-"              safely  rely on being able to disable potentially dangerous pro-\n"
 , stdout);
  fputs(
+"              safely  rely on being able to disable potentially dangerous pro-\n"
 "              tocols, without relying upon support  for  that  protocol  being\n"
 "              built into curl to avoid an error.\n"
 "\n"
 "              This option can be used multiple times, in which case the effect\n"
 "              is the same as concatenating the protocols into one instance  of\n"
 "              the option.\n"
 "\n"
 "              (Added in 7.20.2)\n"
 "\n"
 "       --proto-redir <protocols>\n"
-"              Tells  curl  to  use  the listed protocols after a redirect. See\n"
 , stdout);
  fputs(
+"              Tells  curl  to  use  the listed protocols after a redirect. See\n"
 "              --proto for how protocols are represented.\n"
 "\n"
 "              (Added in 7.20.2)\n"
 "\n"
 "       --proxy-anyauth\n"
 "              Tells curl to pick a suitable authentication method when  commu-\n"
 "              nicating  with  the  given  proxy.  This  might  cause  an extra\n"
 "              request/response round-trip. (Added in 7.13.2)\n"
 "\n"
 "       --proxy-basic\n"
-"              Tells curl to use HTTP Basic authentication  when  communicating\n"
 , stdout);
  fputs(
+"              Tells curl to use HTTP Basic authentication  when  communicating\n"
 "              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
 "              remote host. Basic is the  default  authentication  method  curl\n"
 "              uses with proxies.\n"
 "\n"
 "       --proxy-digest\n"
 "              Tells  curl to use HTTP Digest authentication when communicating\n"
 "              with the given proxy. Use --digest for enabling HTTP Digest with\n"
 "              a remote host.\n"
 "\n"
-"       --proxy-negotiate\n"
 , stdout);
  fputs(
+"       --proxy-negotiate\n"
 "              Tells curl to use HTTP Negotiate authentication when communicat-\n"
 "              ing with the given proxy.  Use  --negotiate  for  enabling  HTTP\n"
 "              Negotiate with a remote host. (Added in 7.17.1)\n"
 "\n"
 "       --proxy-ntlm\n"
 "              Tells  curl  to  use HTTP NTLM authentication when communicating\n"
