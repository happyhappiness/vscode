 "       repeated use of the same command line option.)\n"
 "\n"
 "       -#, --progress-bar\n"
 "              Make curl display progress as a simple progress bar  instead  of\n"
 "              the standard, more informational, meter.\n"
 "\n"
-"       -0, --http1.0\n"
+"       -:, --next\n"
 , stdout);
  fputs(
+"              Tells curl to use a separate operation for the following URL and\n"
+"              associated  options.  This  allows  you  to  send  several   URL\n"
+"              requests,  each  with  their  own specific options, for example,\n"
+"              such as different user names or custom requests for each. (Added\n"
+"              in 7.36.0)\n"
+"\n"
+"       -0, --http1.0\n"
 "              (HTTP)  Tells  curl to use HTTP version 1.0 instead of using its\n"
 "              internally preferred: HTTP 1.1.\n"
 "\n"
+, stdout);
+ fputs(
 "       --http1.1\n"
 "              (HTTP) Tells curl to use HTTP version 1.1. This is the  internal\n"
 "              default version. (Added in 7.33.0)\n"
 "\n"
-"       --http2.0\n"
-"              (HTTP)  Tells  curl  to  issue its requests using HTTP 2.0. This\n"
+"       --http2\n"
+"              (HTTP)  Tells  curl  to  issue  its  requests using HTTP 2. This\n"
 "              requires that the underlying libcurl was built  to  support  it.\n"
 "              (Added in 7.33.0)\n"
 "\n"
-"       -1, --tlsv1\n"
+"       --no-npn\n"
+"              Disable  the  NPN  TLS  extension.  NPN is enabled by default if\n"
+, stdout);
+ fputs(
+"              libcurl was built with an SSL library that supports NPN. NPN  is\n"
+"              used  by a libcurl that supports HTTP 2 to negotiate HTTP 2 sup-\n"
+"              port with the server during https sessions.\n"
+"\n"
+"              (Added in 7.36.0)\n"
+"\n"
+"       --no-alpn\n"
+"              Disable the ALPN TLS extension. ALPN is enabled  by  default  if\n"
+"              libcurl  was  built with an SSL library that supports ALPN. ALPN\n"
 , stdout);
  fputs(
-"              (SSL)  Forces  curl to use TLS version 1 when negotiating with a\n"
-"              remote TLS server.\n"
+"              is used by a libcurl that supports HTTP 2 to  negotiate  HTTP  2\n"
+"              support with the server during https sessions.\n"
+"\n"
+"              (Added in 7.36.0)\n"
 "\n"
+"       -1, --tlsv1\n"
+"              (SSL) Forces curl to use TLS version 1.x when negotiating with a\n"
+"              remote TLS server.  You can use  options  --tlsv1.0,  --tlsv1.1,\n"
+"              and  --tlsv1.2 to control the TLS version more precisely (if the\n"
+"              SSL backend in use supports such a level of control).\n"
+"\n"
+, stdout);
+ fputs(
 "       -2, --sslv2\n"
 "              (SSL) Forces curl to use SSL version 2 when negotiating  with  a\n"
 "              remote SSL server.\n"
 "\n"
 "       -3, --sslv3\n"
 "              (SSL)  Forces  curl to use SSL version 3 when negotiating with a\n"
 "              remote SSL server.\n"
 "\n"
 "       -4, --ipv4\n"
 "              If curl is capable of resolving an address to multiple  IP  ver-\n"
-, stdout);
- fputs(
 "              sions  (which  it  is  if it is IPv6-capable), this option tells\n"
 "              curl to resolve names to IPv4 addresses only.\n"
+, stdout);
+ fputs(
 "\n"
 "       -6, --ipv6\n"
 "              If curl is capable of resolving an address to multiple  IP  ver-\n"
 "              sions  (which  it  is  if it is IPv6-capable), this option tells\n"
 "              curl to resolve names to IPv6 addresses only.\n"
 "\n"
 "       -a, --append\n"
 "              (FTP/SFTP) When used in an upload, this will tell curl to append\n"
-, stdout);
- fputs(
 "              to  the  target  file  instead  of  overwriting  it. If the file\n"
 "              doesn't exist, it will be  created.   Note  that  this  flag  is\n"
+, stdout);
+ fputs(
 "              ignored by some SSH servers (including OpenSSH).\n"
 "\n"
 "       -A, --user-agent <agent string>\n"
 "              (HTTP) Specify the User-Agent string to send to the HTTP server.\n"
 "              Some  badly  done  CGIs  fail  if  this  field  isn't   set   to\n"
 "              \"Mozilla/4.0\".  To  encode  blanks  in  the string, surround the\n"
-, stdout);
- fputs(
 "              string with single quote marks. This can also be  set  with  the\n"
 "              -H, --header option of course.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --anyauth\n"
 "              (HTTP) Tells curl to figure out authentication method by itself,\n"
 "              and use the most secure one the remote site claims  to  support.\n"
 "              This is done by first doing a request and checking the response-\n"
-, stdout);
- fputs(
 "              headers, thus possibly inducing  an  extra  network  round-trip.\n"
 "              This  is  used  instead  of  setting  a  specific authentication\n"
+, stdout);
+ fputs(
 "              method, which you can do with  --basic,  --digest,  --ntlm,  and\n"
 "              --negotiate.\n"
 "\n"
 "              Note  that  using --anyauth is not recommended if you do uploads\n"
 "              from stdin, since it may require data to be sent twice and  then\n"
-, stdout);
- fputs(
 "              the client must be able to rewind. If the need should arise when\n"
 "              uploading from stdin, the upload operation will fail.\n"
 "\n"
 "       -b, --cookie <name=data>\n"
+, stdout);
+ fputs(
 "              (HTTP) Pass the data to the HTTP server as a cookie. It is  sup-\n"
 "              posedly  the data previously received from the server in a \"Set-\n"
 "              Cookie:\" line.  The data should be in the format  \"NAME1=VALUE1;\n"
 "              NAME2=VALUE2\".\n"
 "\n"
-, stdout);
- fputs(
 "              If  no  '=' symbol is used in the line, it is treated as a file-\n"
 "              name to use to read previously stored cookie lines  from,  which\n"
+, stdout);
+ fputs(
 "              should  be used in this session if they match. Using this method\n"
 "              also activates the \"cookie parser\" which will make  curl  record\n"
 "              incoming cookies too, which may be handy if you're using this in\n"
 "              combination with the -L, --location option. The file  format  of\n"
-, stdout);
- fputs(
 "              the  file  to  read cookies from should be plain HTTP headers or\n"
 "              the Netscape/Mozilla cookie file format.\n"
 "\n"
+, stdout);
+ fputs(
 "              NOTE that the file specified with -b, --cookie is only  used  as\n"
 "              input.  No cookies will be stored in the file. To store cookies,\n"
 "              use the -c, --cookie-jar option or you could even save the  HTTP\n"
 "              headers to a file using -D, --dump-header!\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -B, --use-ascii\n"
 "              (FTP/LDAP)  Enable  ASCII  transfer.  For  FTP, this can also be\n"
+, stdout);
+ fputs(
 "              enforced by using an URL that ends with \";type=A\".  This  option\n"
 "              causes data sent to stdout to be in text mode for win32 systems.\n"
 "\n"
 "       --basic\n"
 "              (HTTP)  Tells curl to use HTTP Basic authentication. This is the\n"
-, stdout);
- fputs(
 "              default and this option is usually pointless, unless you use  it\n"
 "              to  override  a  previously  set  option  that  sets a different\n"
 "              authentication method (such as --ntlm,  --digest,  or  --negoti-\n"
+, stdout);
+ fputs(
 "              ate).\n"
 "\n"
 "       -c, --cookie-jar <file name>\n"
 "              (HTTP)  Specify to which file you want curl to write all cookies\n"
 "              after a completed operation. Curl writes all cookies  previously\n"
-, stdout);
- fputs(
 "              read  from a specified file as well as all cookies received from\n"
 "              remote server(s). If no cookies are known, no file will be writ-\n"
 "              ten.  The  file  will  be written using the Netscape cookie file\n"
+, stdout);
+ fputs(
 "              format. If you set the file name to  a  single  dash,  \"-\",  the\n"
 "              cookies will be written to stdout.\n"
 "\n"
 "              This  command  line  option will activate the cookie engine that\n"
-, stdout);
- fputs(
 "              makes curl record and use cookies. Another way to activate it is\n"
 "              to use the -b, --cookie option.\n"
 "\n"
 "              If the cookie jar can't be created or written to, the whole curl\n"
 "              operation won't fail or even report an error clearly.  Using  -v\n"
+, stdout);
+ fputs(
 "              will get a warning displayed, but that is the only visible feed-\n"
 "              back you get about this possibly lethal situation.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the  last  specified  file\n"
 "              name will be used.\n"
 "\n"
 "       -C, --continue-at <offset>\n"
 "              Continue/Resume  a  previous  file transfer at the given offset.\n"
 "              The given offset is the exact  number  of  bytes  that  will  be\n"
-"              skipped,  counting  from the beginning of the source file before\n"
-"              it is transferred to the destination.  If used with uploads, the\n"
 , stdout);
  fputs(
+"              skipped,  counting  from the beginning of the source file before\n"
+"              it is transferred to the destination.  If used with uploads, the\n"
 "              FTP server command SIZE will not be used by curl.\n"
 "\n"
 "              Use  \"-C  -\" to tell curl to automatically find out where/how to\n"
 "              resume the transfer. It then uses the given  output/input  files\n"
 "              to figure that out.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-"       --ciphers <list of ciphers>\n"
-"              (SSL) Specifies which ciphers to use in the connection. The list\n"
 , stdout);
  fputs(
+"       --ciphers <list of ciphers>\n"
+"              (SSL) Specifies which ciphers to use in the connection. The list\n"
 "              of ciphers must specify valid ciphers. Read  up  on  SSL  cipher\n"
 "              list           details           on           this          URL:\n"
 "              http://www.openssl.org/docs/apps/ciphers.html\n"
 "\n"
 "              NSS ciphers are done differently than OpenSSL  and  GnuTLS.  The\n"
 "              full  list of NSS ciphers is in the NSSCipherSuite entry at this\n"
-"              URL:                                          http://git.fedora-\n"
 , stdout);
  fputs(
+"              URL:                                          http://git.fedora-\n"
 "              hosted.org/cgit/mod_nss.git/plain/docs/mod_nss.html#Directives\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --compressed\n"
 "              (HTTP) Request a compressed response using one of the algorithms\n"
 "              curl supports, and save  the  uncompressed  document.   If  this\n"
 "              option  is  used  and  the server sends an unsupported encoding,\n"
+, stdout);
+ fputs(
 "              curl will report an error.\n"
 "\n"
 "       --connect-timeout <seconds>\n"
-, stdout);
- fputs(
 "              Maximum time in seconds that you allow  the  connection  to  the\n"
 "              server  to  take.   This  only limits the connection phase, once\n"
 "              curl has connected this option is of no more use.  Since 7.32.0,\n"
 "              this  option accepts decimal values, but the actual timeout will\n"
 "              decrease in accuracy as the specified timeout increases in deci-\n"
-"              mal precision. See also the -m, --max-time option.\n"
-"\n"
 , stdout);
  fputs(
+"              mal precision. See also the -m, --max-time option.\n"
+"\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --create-dirs\n"
 "              When  used  in  conjunction with the -o option, curl will create\n"
 "              the necessary local directory hierarchy as needed.  This  option\n"
 "              creates  the dirs mentioned with the -o option, nothing else. If\n"
 "              the -o file name uses no dir or if the dirs it mentions  already\n"
-"              exist, no dir will be created.\n"
-"\n"
 , stdout);
  fputs(
+"              exist, no dir will be created.\n"
+"\n"
 "              To  create remote directories when using FTP or SFTP, try --ftp-\n"
 "              create-dirs.\n"
 "\n"
 "       --crlf (FTP) Convert LF to CRLF in upload. Useful for MVS (OS/390).\n"
 "\n"
 "       --crlfile <file>\n"
 "              (HTTPS/FTPS) Provide a file using PEM format with a  Certificate\n"
 "              Revocation  List  that may specify peer certificates that are to\n"
 "              be considered revoked.\n"
 "\n"
-"              If this option is used several times, the last one will be used.\n"
-"\n"
 , stdout);
  fputs(
+"              If this option is used several times, the last one will be used.\n"
+"\n"
 "              (Added in 7.19.7)\n"
 "       -d, --data <data>\n"
 "              (HTTP) Sends the specified data in a POST request  to  the  HTTP\n"
 "              server,  in  the  same  way  that a browser does when a user has\n"
 "              filled in an HTML form and presses the submit button. This  will\n"
 "              cause curl to pass the data to the server using the content-type\n"
-"              application/x-www-form-urlencoded.  Compare to -F, --form.\n"
-"\n"
 , stdout);
  fputs(
+"              application/x-www-form-urlencoded.  Compare to -F, --form.\n"
+"\n"
 "              -d, --data is the same as  --data-ascii.  To  post  data  purely\n"
 "              binary, you should instead use the --data-binary option. To URL-\n"
 "              encode the value of a form field you may use --data-urlencode.\n"
 "\n"
 "              If any of these options is used more than once on the same  com-\n"
 "              mand  line,  the  data  pieces specified will be merged together\n"
-"              with a separating  &-symbol.  Thus,  using  '-d  name=daniel  -d\n"
 , stdout);
  fputs(
+"              with a separating  &-symbol.  Thus,  using  '-d  name=daniel  -d\n"
 "              skill=lousy'  would  generate  a  post  chunk  that  looks  like\n"
 "              'name=daniel&skill=lousy'.\n"
 "\n"
 "              If you start the data with the letter @, the rest  should  be  a\n"
 "              file  name  to read the data from, or - if you want curl to read\n"
 "              the data from stdin. Multiple files can also be specified. Post-\n"
-"              ing  data  from  a  file  named 'foobar' would thus be done with\n"
 , stdout);
  fputs(
+"              ing  data  from  a  file  named 'foobar' would thus be done with\n"
 "              --data @foobar. When --data is told to read  from  a  file  like\n"
 "              that, carriage returns and newlines will be stripped out.\n"
 "\n"
 "       -D, --dump-header <file>\n"
 "              Write the protocol headers to the specified file.\n"
 "\n"
 "              This  option  is handy to use when you want to store the headers\n"
 "              that an HTTP site sends to you. Cookies from the  headers  could\n"
-"              then  be  read  in  a  second  curl  invocation by using the -b,\n"
 , stdout);
  fputs(
+"              then  be  read  in  a  second  curl  invocation by using the -b,\n"
 "              --cookie option! The -c, --cookie-jar option is however a better\n"
 "              way to store cookies.\n"
 "\n"
 "              When  used  in FTP, the FTP server response lines are considered\n"
 "              being \"headers\" and thus are saved there.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --data-ascii <data>\n"
 "              See -d, --data.\n"
 "\n"
 "       --data-binary <data>\n"
-"              (HTTP) This posts data exactly as specified with no  extra  pro-\n"
 , stdout);
  fputs(
+"              (HTTP) This posts data exactly as specified with no  extra  pro-\n"
 "              cessing whatsoever.\n"
 "\n"
 "              If  you  start  the data with the letter @, the rest should be a\n"
 "              filename.  Data is posted in a similar  manner  as  --data-ascii\n"
 "              does,  except  that  newlines and carriage returns are preserved\n"
 "              and conversions are never done.\n"
 "\n"
 "              If this option is used several times,  the  ones  following  the\n"
+, stdout);
+ fputs(
 "              first will append data as described in -d, --data.\n"
 "\n"
 "       --data-urlencode <data>\n"
-, stdout);
- fputs(
 "              (HTTP) This posts data, similar to the other --data options with\n"
 "              the exception that this performs URL-encoding. (Added in 7.18.0)\n"
 "              To be CGI-compliant, the <data> part should begin  with  a  name\n"
 "              followed  by a separator and a content specification. The <data>\n"
 "              part can be passed to curl using one of the following syntaxes:\n"
 "\n"
-"              content\n"
-"                     This will make curl URL-encode the content and pass  that\n"
 , stdout);
  fputs(
+"              content\n"
+"                     This will make curl URL-encode the content and pass  that\n"
 "                     on.  Just  be careful so that the content doesn't contain\n"
 "                     any = or @ symbols, as that will  then  make  the  syntax\n"
 "                     match one of the other cases below!\n"
 "\n"
 "              =content\n"
 "                     This  will make curl URL-encode the content and pass that\n"
 "                     on. The preceding = symbol is not included in the data.\n"
 "\n"
-"              name=content\n"
 , stdout);
  fputs(
+"              name=content\n"
 "                     This will make curl URL-encode the content part and  pass\n"
 "                     that  on.  Note that the name part is expected to be URL-\n"
 "                     encoded already.\n"
 "\n"
 "              @filename\n"
 "                     This will  make  curl  load  data  from  the  given  file\n"
