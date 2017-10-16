 "       show the --option version of them. (This concept with --no options  was\n"
 , stdout);
  fputs(
 "       added  in  7.19.0.  Previously  most  options  were  toggled  on/off on\n"
 "       repeated use of the same command line option.)\n"
 "\n"
-"       -a/--append\n"
+"       -#, --progress-bar\n"
+"              Make curl display progress information as a progress bar instead\n"
+"              of the\n"
+"\n"
+"       -0, --http1.0\n"
+"              (HTTP)  Forces curl to issue its requests using HTTP 1.0 instead\n"
+"              of using its internally preferred: HTTP 1.1.\n"
+"\n"
+"       -1, --tlsv1\n"
+, stdout);
+ fputs(
+"              (SSL) Forces curl to use TLS version 1 when negotiating  with  a\n"
+"              remote TLS server.\n"
+"\n"
+"       -2, --sslv2\n"
+"              (SSL)  Forces  curl to use SSL version 2 when negotiating with a\n"
+"              remote SSL server.\n"
+"\n"
+"       -3, --sslv3\n"
+"              (SSL) Forces curl to use SSL version 3 when negotiating  with  a\n"
+"              remote SSL server.\n"
+"\n"
+"       -4, --ipv4\n"
+"              If  libcurl  is  capable  of resolving an address to multiple IP\n"
+, stdout);
+ fputs(
+"              versions (which it is if it is IPv6-capable), this option  tells\n"
+"              libcurl to resolve names to IPv4 addresses only.\n"
+"\n"
+"       -6, --ipv6\n"
+"              If  libcurl  is  capable  of resolving an address to multiple IP\n"
+"              versions (which it is if it is IPv6-capable), this option  tells\n"
+"              libcurl  to  resolve names to IPv6 addresses only.  default sta-\n"
+"              tistics.\n"
+"\n"
+"       -a, --append\n"
+, stdout);
+ fputs(
 "              (FTP/SFTP) When used in an upload, this will tell curl to append\n"
 "              to  the  target  file  instead  of  overwriting  it. If the file\n"
 "              doesn't exist, it will be  created.   Note  that  this  flag  is\n"
 "              ignored by some SSH servers (including OpenSSH).\n"
 "\n"
-"       -A/--user-agent <agent string>\n"
-, stdout);
- fputs(
+"       -A, --user-agent <agent string>\n"
 "              (HTTP) Specify the User-Agent string to send to the HTTP server.\n"
 "              Some  badly  done  CGIs  fail  if  this  field  isn't   set   to\n"
+, stdout);
+ fputs(
 "              \"Mozilla/4.0\".  To  encode  blanks  in  the string, surround the\n"
 "              string with single quote marks. This can also be  set  with  the\n"
-"              -H/--header option of course.\n"
+"              -H, --header option of course.\n"
 "\n"
 "              If  this  option is set more than once, the last one will be the\n"
 "              one that's used.\n"
 "\n"
 "       --anyauth\n"
-, stdout);
- fputs(
 "              (HTTP) Tells curl to figure out authentication method by itself,\n"
 "              and  use  the most secure one the remote site claims to support.\n"
+, stdout);
+ fputs(
 "              This is done by first doing a request and checking the response-\n"
 "              headers,  thus  possibly  inducing  an extra network round-trip.\n"
 "              This is  used  instead  of  setting  a  specific  authentication\n"
 "              method,  which  you  can  do with --basic, --digest, --ntlm, and\n"
-, stdout);
- fputs(
 "              --negotiate.\n"
 "\n"
 "              Note that using --anyauth is not recommended if you  do  uploads\n"
+, stdout);
+ fputs(
 "              from  stdin, since it may require data to be sent twice and then\n"
 "              the client must be able to rewind. If the need should arise when\n"
 "              uploading from stdin, the upload operation will fail.\n"
 "\n"
-"       -b/--cookie <name=data>\n"
+"       -b, --cookie <name=data>\n"
 "              (HTTP)  Pass the data to the HTTP server as a cookie. It is sup-\n"
-, stdout);
- fputs(
 "              posedly the data previously received from the server in a  \"Set-\n"
 "              Cookie:\"  line.  The data should be in the format \"NAME1=VALUE1;\n"
+, stdout);
+ fputs(
 "              NAME2=VALUE2\".\n"
 "\n"
 "              If no '=' symbol is used in the line, it is treated as  a  file-\n"
 "              name  to  use to read previously stored cookie lines from, which\n"
 "              should be used in this session if they match. Using this  method\n"
-, stdout);
- fputs(
 "              also  activates  the \"cookie parser\" which will make curl record\n"
 "              incoming cookies too, which may be handy if you're using this in\n"
-"              combination  with  the  -L/--location option. The file format of\n"
+, stdout);
+ fputs(
+"              combination  with  the -L, --location option. The file format of\n"
 "              the file to read cookies from should be plain  HTTP  headers  or\n"
 "              the Netscape/Mozilla cookie file format.\n"
 "\n"
-"              NOTE  that  the  file specified with -b/--cookie is only used as\n"
+"              NOTE  that  the file specified with -b, --cookie is only used as\n"
+"              input. No cookies will be stored in the file. To store  cookies,\n"
+"              use  the -c, --cookie-jar option or you could even save the HTTP\n"
 , stdout);
  fputs(
-"              input. No cookies will be stored in the file. To store  cookies,\n"
-"              use  the  -c/--cookie-jar option or you could even save the HTTP\n"
-"              headers to a file using -D/--dump-header!\n"
+"              headers to a file using -D, --dump-header!\n"
 "\n"
 "              If this option is set more than once, the last one will  be  the\n"
 "              one that's used.\n"
 "\n"
-"       -B/--use-ascii\n"
+"       -B, --use-ascii\n"
 "              Enable  ASCII transfer when using FTP or LDAP. For FTP, this can\n"
-, stdout);
- fputs(
 "              also be enforced by using an URL that ends with \";type=A\".  This\n"
 "              option  causes  data sent to stdout to be in text mode for win32\n"
 "              systems.\n"
 "\n"
 "       --basic\n"
+, stdout);
+ fputs(
 "              (HTTP) Tells curl to use HTTP Basic authentication. This is  the\n"
 "              default  and this option is usually pointless, unless you use it\n"
 "              to override a  previously  set  option  that  sets  a  different\n"
-, stdout);
- fputs(
 "              authentication  method  (such  as --ntlm, --digest, or --negoti-\n"
 "              ate).\n"
 "\n"
+"       -c, --cookie-jar <file name>\n"
+"              Specify to which file you want curl to write all cookies after a\n"
+, stdout);
+ fputs(
+"              completed  operation.  Curl  writes  all cookies previously read\n"
+"              from a specified file as  well  as  all  cookies  received  from\n"
+"              remote server(s). If no cookies are known, no file will be writ-\n"
+"              ten. The file will be written using  the  Netscape  cookie  file\n"
+"              format.  If  you  set  the  file name to a single dash, \"-\", the\n"
+"              cookies will be written to stdout.\n"
+"\n"
+, stdout);
+ fputs(
+"              NOTE If the cookie jar can't be created or written to, the whole\n"
+"              curl operation won't fail or even report an error clearly. Using\n"
+"              -v will get a warning displayed, but that is  the  only  visible\n"
+"              feedback you get about this possibly lethal situation.\n"
+"\n"
+"              If  this  option  is used several times, the last specified file\n"
+"              name will be used.\n"
+"\n"
+"       -C, --continue-at <offset>\n"
+, stdout);
+ fputs(
+"              Continue/Resume a previous file transfer at  the  given  offset.\n"
+"              The  given  offset  is  the  exact  number of bytes that will be\n"
+"              skipped, counting from the beginning of the source  file  before\n"
+"              it is transferred to the destination.  If used with uploads, the\n"
+"              FTP server command SIZE will not be used by curl.\n"
+"\n"
+"              Use \"-C -\" to tell curl to automatically find out  where/how  to\n"
+, stdout);
+ fputs(
+"              resume  the  transfer. It then uses the given output/input files\n"
+"              to figure that out.\n"
+"\n"
+"              If this option is used several times, the last one will be used.\n"
+"\n"
 "       --ciphers <list of ciphers>\n"
 "              (SSL) Specifies which ciphers to use in the connection. The list\n"
 "              of  ciphers  must  specify  valid ciphers. Read up on SSL cipher\n"
 "              list          details           on           this           URL:\n"
-"              http://www.openssl.org/docs/apps/ciphers.html\n"
-"\n"
 , stdout);
  fputs(
+"              http://www.openssl.org/docs/apps/ciphers.html\n"
+"\n"
 "              NSS  ciphers  are  done differently than OpenSSL and GnuTLS. The\n"
 "              full list of NSS ciphers is in the NSSCipherSuite entry at  this\n"
 "              URL: http://directory.fedora.redhat.com/docs/mod_nss.html#Direc-\n"
 "              tives\n"
 "\n"
 "              If this option is used several times, the last one will override\n"
 "              the others.\n"
 "\n"
 "       --compressed\n"
-"              (HTTP) Request a compressed response using one of the algorithms\n"
 , stdout);
  fputs(
+"              (HTTP) Request a compressed response using one of the algorithms\n"
 "              libcurl supports, and save the uncompressed document.   If  this\n"
 "              option  is  used  and  the server sends an unsupported encoding,\n"
 "              curl will report an error.\n"
 "\n"
 "       --connect-timeout <seconds>\n"
 "              Maximum time in seconds that you allow  the  connection  to  the\n"
 "              server  to  take.   This  only limits the connection phase, once\n"
-"              curl has connected this option is of no more use. See  also  the\n"
-, stdout);
- fputs(
-"              -m/--max-time option.\n"
-"\n"
-"              If this option is used several times, the last one will be used.\n"
-"\n"
-"       -c/--cookie-jar <file name>\n"
-"              Specify to which file you want curl to write all cookies after a\n"
-"              completed operation. Curl writes  all  cookies  previously  read\n"
-"              from  a  specified  file  as  well  as all cookies received from\n"
-"              remote server(s). If no cookies are known, no file will be writ-\n"
-, stdout);
- fputs(
-"              ten.  The  file  will  be written using the Netscape cookie file\n"
-"              format. If you set the file name to  a  single  dash,  \"-\",  the\n"
-"              cookies will be written to stdout.\n"
-"\n"
-"              NOTE If the cookie jar can't be created or written to, the whole\n"
-"              curl operation won't fail or even report an error clearly. Using\n"
-"              -v  will  get  a warning displayed, but that is the only visible\n"
-, stdout);
- fputs(
-"              feedback you get about this possibly lethal situation.\n"
-"\n"
-"              If this option is used several times, the  last  specified  file\n"
-"              name will be used.\n"
-"\n"
-"       -C/--continue-at <offset>\n"
-"              Continue/Resume  a  previous  file transfer at the given offset.\n"
-"              The given offset is the exact  number  of  bytes  that  will  be\n"
-"              skipped,  counting  from the beginning of the source file before\n"
 , stdout);
  fputs(
-"              it is transferred to the destination.  If used with uploads, the\n"
-"              FTP server command SIZE will not be used by curl.\n"
-"\n"
-"              Use  \"-C  -\" to tell curl to automatically find out where/how to\n"
-"              resume the transfer. It then uses the given  output/input  files\n"
-"              to figure that out.\n"
+"              curl has connected this option is of no more use. See  also  the\n"
+"              -m, --max-time option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --create-dirs\n"
-, stdout);
- fputs(
 "              When  used  in  conjunction with the -o option, curl will create\n"
 "              the necessary local directory hierarchy as needed.  This  option\n"
 "              creates  the dirs mentioned with the -o option, nothing else. If\n"
+, stdout);
+ fputs(
 "              the -o file name uses no dir or if the dirs it mentions  already\n"
 "              exist, no dir will be created.\n"
 "\n"
 "              To  create remote directories when using FTP or SFTP, try --ftp-\n"
 "              create-dirs.\n"
 "\n"
-, stdout);
- fputs(
 "       --crlf (FTP) Convert LF to CRLF in upload. Useful for MVS (OS/390).\n"
 "\n"
 "       --crlfile <file>\n"
 "              (HTTPS/FTPS) Provide a file using PEM format with a  Certificate\n"
 "              Revocation  List  that may specify peer certificates that are to\n"
+, stdout);
+ fputs(
 "              be considered revoked.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              (Added in 7.19.7)\n"
-"\n"
-"       -d/--data <data>\n"
-, stdout);
- fputs(
+"       -d, --data <data>\n"
 "              (HTTP) Sends the specified data in a POST request  to  the  HTTP\n"
 "              server,  in  the  same  way  that a browser does when a user has\n"
 "              filled in an HTML form and presses the submit button. This  will\n"
 "              cause curl to pass the data to the server using the content-type\n"
-"              application/x-www-form-urlencoded.  Compare to -F/--form.\n"
-"\n"
-"              -d/--data is the same  as  --data-ascii.  To  post  data  purely\n"
 , stdout);
  fputs(
+"              application/x-www-form-urlencoded.  Compare to -F, --form.\n"
+"\n"
+"              -d, --data is the same as  --data-ascii.  To  post  data  purely\n"
 "              binary, you should instead use the --data-binary option. To URL-\n"
 "              encode the value of a form field you may use --data-urlencode.\n"
 "\n"
 "              If any of these options is used more than once on the same  com-\n"
 "              mand  line,  the  data  pieces specified will be merged together\n"
-"              with a separating  &-symbol.  Thus,  using  '-d  name=daniel  -d\n"
-"              skill=lousy'  would  generate  a  post  chunk  that  looks  like\n"
 , stdout);
  fputs(
+"              with a separating  &-symbol.  Thus,  using  '-d  name=daniel  -d\n"
+"              skill=lousy'  would  generate  a  post  chunk  that  looks  like\n"
 "              'name=daniel&skill=lousy'.\n"
 "\n"
 "              If you start the data with the letter @, the rest  should  be  a\n"
 "              file  name  to read the data from, or - if you want curl to read\n"
 "              the data from stdin.  The contents of the file must  already  be\n"
+, stdout);
+ fputs(
 "              URL-encoded.  Multiple files can also be specified. Posting data\n"
 "              from a file named 'foobar' would thus be done with --data  @foo-\n"
 "              bar.\n"
 "\n"
+"       -D, --dump-header <file>\n"
+"              Write the protocol headers to the specified file.\n"
+"\n"
+"              This  option  is handy to use when you want to store the headers\n"
+"              that a HTTP site sends to you. Cookies from  the  headers  could\n"
+, stdout);
+ fputs(
+"              then  be  read  in  a  second  curl  invocation by using the -b,\n"
+"              --cookie option! The -c, --cookie-jar option is however a better\n"
+"              way to store cookies.\n"
+"\n"
+"              When  used  in FTP, the FTP server response lines are considered\n"
+"              being \"headers\" and thus are saved there.\n"
+"\n"
+"              If this option is used several times, the last one will be used.\n"
+"              IP \"--data-ascii <data>\" See -d, --data.\n"
+"\n"
 "       --data-binary <data>\n"
 , stdout);
  fputs(
 "              (HTTP)  This  posts data exactly as specified with no extra pro-\n"
 "              cessing whatsoever.\n"
 "\n"
