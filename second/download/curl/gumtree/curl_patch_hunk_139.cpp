 "              or\n"
 "\n"
 , stdout);
  fputs(
 "              curl -F \"name=daniel;type=text/foo\" url.com\n"
 "\n"
+"              You can also explicitly change the name field of an file  upload\n"
+"              part by setting filename=, like this:\n"
+"\n"
+"              curl -F \"file=@localfile;filename=nameinpost\" url.com\n"
+"\n"
 "              See further examples and details in the MANUAL.\n"
 "\n"
 "              This option can be used multiple times.\n"
 "\n"
+"       --form-string <name=string>\n"
+"              (HTTP)  Similar  to  --form except that the value string for the\n"
+, stdout);
+ fputs(
+"              named parameter is used literally. Leading '@' and  '<'  charac-\n"
+"              ters, and the ';type=' string in the value have no special mean-\n"
+"              ing. Use this in preference to --form if there's any possibility\n"
+"              that  the  string  value may accidentally trigger the '@' or '<'\n"
+"              features of --form.\n"
+"\n"
 "       -g/--globoff\n"
 "              This option switches off the \"URL globbing parser\". When you set\n"
-"              this  option, you can specify URLs that contain the letters {}[]\n"
-"              without having them being interpreted by curl itself. Note  that\n"
 , stdout);
  fputs(
+"              this  option, you can specify URLs that contain the letters {}[]\n"
+"              without having them being interpreted by curl itself. Note  that\n"
 "              these  letters are not normal legal URL contents but they should\n"
 "              be encoded according to the URI standard.\n"
 "\n"
 "       -G/--get\n"
 "              When used,  this  option  will  make  all  data  specified  with\n"
 "              -d/--data  or  --data-binary  to  be  used in a HTTP GET request\n"
+, stdout);
+ fputs(
 "              instead of the POST request that otherwise would  be  used.  The\n"
 "              data will be appended to the URL with a '?'  separator.\n"
 "\n"
-, stdout);
- fputs(
 "              If  used  in  combination with -I, the POST data will instead be\n"
 "              appended to the URL with a HEAD request.\n"
 "\n"
 "              If used multiple times, nothing special happens.\n"
 "\n"
 "       -h/--help\n"
 "              Usage help.\n"
 "\n"
 "       -H/--header <header>\n"
 "              (HTTP) Extra header to use when getting  a  web  page.  You  may\n"
-"              specify any number of extra headers. Note that if you should add\n"
 , stdout);
  fputs(
+"              specify any number of extra headers. Note that if you should add\n"
 "              a custom header that has the same name as one  of  the  internal\n"
 "              ones  curl  would  use,  your externally set header will be used\n"
 "              instead of the internal one. This allows you to make even trick-\n"
 "              ier  stuff  than  curl would normally do. You should not replace\n"
 "              internally set  headers  without  knowing  perfectly  well  what\n"
-"              you're doing. Replacing an internal header with one without con-\n"
 , stdout);
  fputs(
+"              you're doing. Replacing an internal header with one without con-\n"
 "              tent on the right side of the colon  will  prevent  that  header\n"
 "              from appearing.\n"
 "\n"
 "              See also the -A/--user-agent and -e/--referer options.\n"
 "\n"
 "              This  option  can  be  used multiple times to add/replace/remove\n"
 "              multiple headers.\n"
 "\n"
 "       -i/--include\n"
 "              (HTTP) Include the HTTP-header in the  output.  The  HTTP-header\n"
-"              includes  things  like  server-name, date of the document, HTTP-\n"
 , stdout);
  fputs(
+"              includes  things  like  server-name, date of the document, HTTP-\n"
 "              version and more...\n"
 "\n"
 "              If this option is used twice,  the  second  will  again  disable\n"
 "              header include.\n"
 "\n"
 "       --interface <name>\n"
 "              Perform  an operation using a specified interface. You can enter\n"
 "              interface name, IP address or host name. An example  could  look\n"
 "              like:\n"
 "\n"
 "               curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
-"              If this option is used several times, the last one will be used.\n"
-"\n"
 , stdout);
  fputs(
+"              If this option is used several times, the last one will be used.\n"
+"\n"
 "       -I/--head\n"
 "              (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature\n"
 "              the  command  HEAD which this uses to get nothing but the header\n"
 "              of a document. When used on a FTP or FILE  file,  curl  displays\n"
 "              the file size and last modification time only.\n"
 "\n"
 "              If  this  option  is  used  twice, the second will again disable\n"
+, stdout);
+ fputs(
 "              header only.\n"
 "\n"
 "       -j/--junk-session-cookies\n"
-, stdout);
- fputs(
 "              (HTTP) When curl is told to read cookies from a given file, this\n"
 "              option  will  make  it  discard all \"session cookies\". This will\n"
 "              basically have the same effect as if a new session  is  started.\n"
 "              Typical  browsers  always  discard  session cookies when they're\n"
 "              closed down. (Added in 7.9.7)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, each occurrence will  tog-\n"
 "              gle this on/off.\n"
 "\n"
 "       -k/--insecure\n"
-, stdout);
- fputs(
 "              (SSL)  This  option explicitly allows curl to perform \"insecure\"\n"
 "              SSL connections and transfers. Starting with curl 7.10, all  SSL\n"
 "              connections  will be attempted to be made secure by using the CA\n"
 "              certificate bundle installed by default. This makes all  connec-\n"
+, stdout);
+ fputs(
 "              tions  considered  \"insecure\"  to  fail  unless -k/--insecure is\n"
 "              used.\n"
 "\n"
 "              If this option is used twice, the second time will again disable\n"
-, stdout);
- fputs(
 "              it.\n"
 "\n"
 "       --key <key>\n"
 "              (SSL)  Private key file name. Allows you to provide your private\n"
 "              key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --key-type <type>\n"
+, stdout);
+ fputs(
 "              (SSL)  Private key file type. Specify which type your --key pro-\n"
 "              vided private key is. DER, PEM and ENG are supported.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "       --krb4 <level>\n"
 "              (FTP) Enable kerberos4 authentication and use. The level must be\n"
 "              entered and should be one of 'clear', 'safe', 'confidential'  or\n"
 "              'private'.  Should  you  use  a  level that is not one of these,\n"
+, stdout);
+ fputs(
 "              'private' will instead be used.\n"
 "\n"
 "              This option requires that the library was built  with  kerberos4\n"
 "              support.  This  is  not  very common. Use -V/--version to see if\n"
-, stdout);
- fputs(
 "              your curl supports it.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -K/--config <config file>\n"
 "              Specify  which config file to read curl arguments from. The con-\n"
+, stdout);
+ fputs(
 "              fig file is a text file in which command line arguments  can  be\n"
 "              written  which  then will be used as if they were written on the\n"
 "              actual command line. Options and their parameters must be speci-\n"
-, stdout);
- fputs(
 "              fied  on  the same config file line. If the parameter is to con-\n"
 "              tain white spaces, the parameter must be inclosed within quotes.\n"
 "              If  the  first  column  of a config line is a '#' character, the\n"
+, stdout);
+ fputs(
 "              rest of the line will be treated as a comment.\n"
 "\n"
 "              Specify the filename as '-' to make  curl  read  the  file  from\n"
 "              stdin.\n"
 "\n"
 "              Note  that  to  be able to specify a URL in the config file, you\n"
-, stdout);
- fputs(
 "              need to specify it using the --url option,  and  not  by  simply\n"
 "              writing  the  URL  on its own line. So, it could look similar to\n"
 "              this:\n"
 "\n"
 "              url = \"http://curl.haxx.se/docs/\"\n"
 "\n"
+, stdout);
+ fputs(
 "              This option can be used multiple times.\n"
 "\n"
+"              When curl is invoked, it always (unless -q is used) checks for a\n"
+"              default  config  file  and  uses it if found. The default config\n"
+"              file is checked for in the following places in this order:\n"
+"\n"
+"              1) curl tries to find the \"home dir\": It first  checks  for  the\n"
+"              CURL_HOME and then the HOME environment variables. Failing that,\n"
+, stdout);
+ fputs(
+"              it uses getpwuid() on unix-like systems (which returns the  home\n"
+"              dir  given the current user in your system). On Windows, it then\n"
+"              checks for the APPDATA variable, or as a last resort the '%USER-\n"
+"              PROFILE%0lication Data'.\n"
+"\n"
+"              2)  On  windows, if there is no _curlrc file in the home dir, it\n"
+"              checks for one in the same dir the executable curl is placed. On\n"
+, stdout);
+ fputs(
+"              unix-like  systems,  it will simply try to load .curlrc from the\n"
+"              determined home dir.\n"
 "       --limit-rate <speed>\n"
 "              Specify the maximum transfer rate you want  curl  to  use.  This\n"
 "              feature is useful if you have a limited pipe and you'd like your\n"
-, stdout);
- fputs(
 "              transfer not use your entire bandwidth.\n"
 "\n"
 "              The given speed is measured in bytes/second, unless a suffix  is\n"
+, stdout);
+ fputs(
 "              appended.   Appending  'k' or 'K' will count the number as kilo-\n"
 "              bytes, 'm' or M' makes it megabytes while 'g' or  'G'  makes  it\n"
 "              gigabytes. Examples: 200K, 3m and 1G.\n"
 "\n"
 "              If  you  are also using the -Y/--speed-limit option, that option\n"
-, stdout);
- fputs(
 "              will  take  precedence  and  might  cripple  the   rate-limiting\n"
 "              slightly, to help keeping the speed-limit logic working.\n"
 "\n"
 "              This option was introduced in curl 7.10.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -l/--list-only\n"
 "              (FTP) When listing an FTP directory, this switch forces a  name-\n"
 "              only  view.   Especially useful if you want to machine-parse the\n"
-, stdout);
- fputs(
 "              contents of an FTP directory since  the  normal  directory  view\n"
 "              doesn't use a standard look or format.\n"
 "\n"
 "              This  option  causes  an  FTP NLST command to be sent.  Some FTP\n"
+, stdout);
+ fputs(
 "              servers list only files in their response to NLST; they  do  not\n"
 "              include subdirectories and symbolic links.\n"
 "\n"
 "              If this option is used twice, the second will again disable list\n"
 "              only.\n"
 "\n"
 "       -L/--location\n"
-, stdout);
- fputs(
 "              (HTTP/HTTPS) If the server reports that the requested page has a\n"
 "              different  location  (indicated  with the header line Location:)\n"
 "              this flag will let curl attempt to reattempt the get on the  new\n"
+, stdout);
+ fputs(
 "              place.  If used together with -i/--include or -I/--head, headers\n"
 "              from all requested pages will be  shown.  If  authentication  is\n"
 "              used,  curl  will only send its credentials to the initial host,\n"
-, stdout);
- fputs(
 "              so if a redirect takes curl to a different host, it won't inter-\n"
 "              cept  the  user+password.  See also --location-trusted on how to\n"
 "              change this.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used twice,  the  second  will  again  disable\n"
 "              location following.\n"
 "\n"
 "       --location-trusted\n"
 "              (HTTP/HTTPS) Like -L/--location, but will allow sending the name\n"
 "              + password to all hosts that the site may redirect to. This  may\n"
-, stdout);
- fputs(
 "              or may not introduce a security breach if the site redirects you\n"
 "              do a site to which you'll send your authentication  info  (which\n"
+, stdout);
+ fputs(
 "              is plaintext in the case of HTTP Basic authentication).\n"
 "\n"
 "              If  this  option  is  used  twice, the second will again disable\n"
 "              location following.\n"
 "\n"
 "       --max-filesize <bytes>\n"
 "              Specify the maximum size (in bytes) of a file  to  download.  If\n"
-, stdout);
- fputs(
 "              the  file requested is larger than this value, the transfer will\n"
 "              not start and curl will return with exit code 63.\n"
 "\n"
+, stdout);
+ fputs(
 "              NOTE: The file size is not always known prior to  download,  and\n"
 "              for such files this option has no effect even if the file trans-\n"
 "              fer ends up being larger than this given  limit.  This  concerns\n"
 "              both FTP and HTTP transfers.\n"
 "\n"
 "       -m/--max-time <seconds>\n"
-, stdout);
- fputs(
 "              Maximum  time  in  seconds that you allow the whole operation to\n"
 "              take.  This is useful for preventing your batch jobs from  hang-\n"
+, stdout);
+ fputs(
 "              ing  for  hours  due to slow networks or links going down.  This\n"
 "              doesn't work fully in win32 systems.  See  also  the  --connect-\n"
 "              timeout option.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -M/--manual\n"
 "              Manual. Display the huge help text.\n"
 "\n"
-, stdout);
- fputs(
 "       -n/--netrc\n"
 "              Makes curl scan the .netrc file in the user's home directory for\n"
+, stdout);
+ fputs(
 "              login name and password. This is typically used for ftp on unix.\n"
 "              If used with http, curl will  enable  user  authentication.  See\n"
 "              netrc(4) or ftp(1) for details on the file format. Curl will not\n"
 "              complain if that file hasn't the right  permissions  (it  should\n"
 "              not  be  world  nor  group  readable).  The environment variable\n"
-, stdout);
- fputs(
 "              \"HOME\" is used to find the home directory.\n"
 "\n"
+, stdout);
+ fputs(
 "              A quick and very simple example of how  to  setup  a  .netrc  to\n"
 "              allow  curl to ftp to the machine host.domain.com with user name\n"
 "              'myself' and password\n"
 "\n"
 "              machine host.domain.com login myself password secret\n"
 "\n"
 "              If this option is used twice,  the  second  will  again  disable\n"
 "              netrc usage.\n"
 "\n"
 "       --netrc-optional\n"
+"              Very  similar to --netrc, but this option makes the .netrc usage\n"
 , stdout);
  fputs(
-"              Very  similar to --netrc, but this option makes the .netrc usage\n"
 "              optional and not mandatory as the --netrc does.\n"
 "\n"
 "       --negotiate\n"
 "              (HTTP) Enables GSS-Negotiate authentication.  The  GSS-Negotiate\n"
 "              method was designed by Microsoft and is used in their web appli-\n"
 "              cations. It is  primarily  meant  as  a  support  for  Kerberos5\n"
 "              authentication but may be also used along with another authenti-\n"
+"              cation methods. For  more  information  see  IETF  draft  draft-\n"
 , stdout);
  fputs(
-"              cation methods. For  more  information  see  IETF  draft  draft-\n"
 "              brezak-spnego-http-04.txt. (Added in 7.10.6)\n"
 "\n"
 "              This option requires that the library was built with GSSAPI sup-\n"
 "              port. This is not very common. Use -V/--version to see  if  your\n"
 "              version supports GSS-Negotiate.\n"
 "\n"
 "              If  this option is used several times, the following occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -N/--no-buffer\n"
+"              Disables the buffering of the output stream. In normal work sit-\n"
 , stdout);
  fputs(
-"              Disables the buffering of the output stream. In normal work sit-\n"
 "              uations,  curl  will  use a standard buffered output stream that\n"
 "              will have the effect that it will output the data in chunks, not\n"
 "              necessarily  exactly  when  the data arrives.  Using this option\n"
 "              will disable that buffering.\n"
 "\n"
 "              If this option is used twice, the second will  again  switch  on\n"
 "              buffering.\n"
 "\n"
+"       --ntlm (HTTP)  Enables  NTLM  authentication.  The  NTLM authentication\n"
 , stdout);
  fputs(
-"       --ntlm (HTTP)  Enables  NTLM  authentication.  The  NTLM authentication\n"
 "              method was designed by Microsoft and is used by IIS web servers.\n"
 "              It is a proprietary protocol, reversed engineered by clever peo-\n"
 "              ple and implemented in curl based on their efforts. This kind of\n"
 "              behavior  should  not be endorsed, you should encourage everyone\n"
 "              who uses NTLM to switch to a public and  documented  authentica-\n"
-, stdout);
- fputs(
 "              tion method instead. Such as Digest. (Added in 7.10.6)\n"
 "\n"
+, stdout);
+ fputs(
 "              If  you  want to enable NTLM for your proxy authentication, then\n"
 "              use --proxy-ntlm.\n"
 "\n"
 "              This option requires that the library was built  with  SSL  sup-\n"
 "              port. Use -V/--version to see if your curl supports NTLM.\n"
 "\n"
 "              If  this option is used several times, the following occurrences\n"
 "              make no difference.\n"
 "\n"
 "       -o/--output <file>\n"
+"              Write output to <file> instead of stdout. If you are using {} or\n"
 , stdout);
  fputs(
-"              Write output to <file> instead of stdout. If you are using {} or\n"
 "              []  to  fetch  multiple documents, you can use '#' followed by a\n"
 "              number in the <file> specifier. That variable will  be  replaced\n"
 "              with the current string for the URL being fetched. Like in:\n"
 "\n"
 "                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
 "              or use several variables like:\n"
 "\n"
 "                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
 "\n"
+"              You  may  use  this  option  as many times as you have number of\n"
 , stdout);
  fputs(
-"              You  may  use  this  option  as many times as you have number of\n"
 "              URLs.\n"
 "\n"
 "              See also the --create-dirs option to create the  local  directo-\n"
 "              ries dynamically.\n"
 "\n"
 "       -O/--remote-name\n"
 "              Write  output to a local file named like the remote file we get.\n"
 "              (Only the file part of the remote file is used, the path is  cut\n"
 "              off.)\n"
 "\n"
-"              You  may  use  this  option  as many times as you have number of\n"
+"              The  remote  file  name  to use for saving is extracted from the\n"
+"              given URL.  Nothing else\n"
+"\n"
 , stdout);
  fputs(
+"              You may use this option as many times  as  you  have  number  of\n"
 "              URLs.\n"
 "\n"
 "       --pass <phrase>\n"
 "              (SSL) Pass phrase for the private key\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+"       --proxy-anyauth\n"
+"              Tells curl to pick a suitable authentication method when  commu-\n"
+"              nicating  with  the  given  proxy.  This  will  cause  an  extra\n"
+, stdout);
+ fputs(
+"              request/response round-trip. Added in curl 7.13.2.\n"
+"\n"
+"              If this option is used twice, the second will again disable  the\n"
+"              proxy use-any authentication.\n"
+"\n"
 "       --proxy-basic\n"
 "              Tells  curl  to use HTTP Basic authentication when communicating\n"
 "              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
 "              remote  host.  Basic  is  the default authentication method curl\n"
 "              uses with proxies.\n"
 "\n"
