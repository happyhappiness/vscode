 "              (SSL/SSH) Private key file name. Allows you to provide your pri-\n"
 "              vate key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --key-type <type>\n"
-"              (SSL) Private key file type. Specify which type your --key  pro-\n"
+"              (SSL)  Private key file type. Specify which type your --key pro-\n"
 , stdout);
  fputs(
-"              vided  private  key  is. DER, PEM, and ENG are supported. If not\n"
+"              vided private key is. DER, PEM, and ENG are  supported.  If  not\n"
 "              specified, PEM is assumed.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --krb <level>\n"
-"              (FTP) Enable Kerberos authentication and use. The level must  be\n"
+"              (FTP)  Enable Kerberos authentication and use. The level must be\n"
 "              entered and should be one of 'clear', 'safe', 'confidential', or\n"
-"              'private'. Should you use a level that  is  not  one  of  these,\n"
+"              'private'.  Should  you  use  a  level that is not one of these,\n"
 , stdout);
  fputs(
 "              'private' will instead be used.\n"
 "\n"
-"              This  option  requires  a library built with kerberos4 or GSSAPI\n"
+"              This option requires a library built with  kerberos4  or  GSSAPI\n"
 "              (GSS-Negotiate) support. This is not very common. Use -V, --ver-\n"
 "              sion to see if your curl supports it.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -l, --list-only\n"
-"              (FTP)  When listing an FTP directory, this switch forces a name-\n"
+"              (FTP) When listing an FTP directory, this switch forces a  name-\n"
 , stdout);
  fputs(
-"              only view.  Especially useful if you want to  machine-parse  the\n"
-"              contents  of  an  FTP  directory since the normal directory view\n"
-"              doesn't use a standard look or format.\n"
+"              only  view.  This  is  especially  useful  if  the user wants to\n"
+"              machine-parse the contents of an FTP directory since the  normal\n"
+"              directory  view doesn't use a standard look or format. When used\n"
+"              like this, the option causes a NLST command to be  sent  to  the\n"
+"              server instead of LIST.\n"
 "\n"
-"              This option causes an FTP NLST command to  be  sent.   Some  FTP\n"
-"              servers  list  only files in their response to NLST; they do not\n"
-"              include subdirectories and symbolic links.\n"
+"              Note:  Some  FTP  servers  list  only files in their response to\n"
+, stdout);
+ fputs(
+"              NLST; they do not include sub-directories and symbolic links.\n"
 "\n"
-"       -L, --location\n"
+"              (POP3) When retrieving a specific email from POP3,  this  switch\n"
+"              forces  a  LIST command to be performed instead of RETR. This is\n"
+"              particularly useful if the user wants to see if a specific  mes-\n"
+"              sage id exists on the server and what size it is.\n"
+"\n"
+"              Note:  When  combined  with -X, --request <command>, this option\n"
 , stdout);
  fputs(
+"              can be used to send an UIDL command instead, so the user may use\n"
+"              the  email's  unique  identifier  rather than it's message id to\n"
+"              make the request. (Added in 7.21.5)\n"
+"\n"
+"       -L, --location\n"
 "              (HTTP/HTTPS) If the server reports that the requested  page  has\n"
 "              moved to a different location (indicated with a Location: header\n"
 "              and a 3XX response code), this option will make  curl  redo  the\n"
+, stdout);
+ fputs(
 "              request on the new place. If used together with -i, --include or\n"
 "              -I, --head, headers from all requested pages will be shown. When\n"
 "              authentication  is  used, curl only sends its credentials to the\n"
-, stdout);
- fputs(
 "              initial host. If a redirect takes curl to a different  host,  it\n"
 "              won't  be  able to intercept the user+password. See also --loca-\n"
 "              tion-trusted on how to change this. You can limit the amount  of\n"
+, stdout);
+ fputs(
 "              redirects to follow by using the --max-redirs option.\n"
 "\n"
 "              When  curl follows a redirect and the request is not a plain GET\n"
 "              (for example POST or PUT), it will do the following request with\n"
-, stdout);
- fputs(
 "              a GET if the HTTP response was 301, 302, or 303. If the response\n"
 "              code was any other 3xx code, curl  will  re-send  the  following\n"
 "              request using the same unmodified method.\n"
 "\n"
 "       --libcurl <file>\n"
+, stdout);
+ fputs(
 "              Append  this  option  to any ordinary curl command line, and you\n"
 "              will get a libcurl-using C source code written to the file  that\n"
 "              does the equivalent of what your command-line operation does!\n"
 "\n"
-, stdout);
- fputs(
 "              If  this  option is used several times, the last given file name\n"
 "              will be used. (Added in 7.16.1)\n"
 "\n"
 "       --limit-rate <speed>\n"
 "              Specify the maximum transfer rate you want  curl  to  use.  This\n"
+, stdout);
+ fputs(
 "              feature is useful if you have a limited pipe and you'd like your\n"
 "              transfer not to use your entire bandwidth.\n"
 "\n"
 "              The given speed is measured in bytes/second, unless a suffix  is\n"
-, stdout);
- fputs(
 "              appended.   Appending  'k' or 'K' will count the number as kilo-\n"
 "              bytes, 'm' or M' makes it megabytes, while 'g' or 'G'  makes  it\n"
 "              gigabytes. Examples: 200K, 3m and 1G.\n"
 "\n"
+, stdout);
+ fputs(
 "              The  given  rate  is the average speed counted during the entire\n"
 "              transfer. It means that curl might use higher transfer speeds in\n"
 "              short bursts, but over time it uses no more than the given rate.\n"
-, stdout);
- fputs(
 "              If  you  also use the -Y, --speed-limit option, that option will\n"
 "              take precedence and might cripple the rate-limiting slightly, to\n"
 "              help keeping the speed-limit logic working.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --local-port <num>[-num]\n"
 "              Set a preferred number or range of local port numbers to use for\n"
 "              the connection(s).  Note that  port  numbers  by  nature  are  a\n"
-, stdout);
- fputs(
 "              scarce resource that will be busy at times so setting this range\n"
 "              to something too narrow might cause unnecessary connection setup\n"
 "              failures. (Added in 7.15.2)\n"
 "\n"
 "       --location-trusted\n"
+, stdout);
+ fputs(
 "              (HTTP/HTTPS)  Like  -L,  --location,  but will allow sending the\n"
 "              name + password to all hosts that the site may redirect to. This\n"
 "              may or may not introduce a security breach if the site redirects\n"
-, stdout);
- fputs(
 "              you to a site to which  you'll  send  your  authentication  info\n"
 "              (which is plaintext in the case of HTTP Basic authentication).\n"
 "\n"
 "       -m, --max-time <seconds>\n"
+, stdout);
+ fputs(
 "              Maximum  time  in  seconds that you allow the whole operation to\n"
 "              take.  This is useful for preventing your batch jobs from  hang-\n"
 "              ing  for  hours due to slow networks or links going down.  Since\n"
-, stdout);
- fputs(
 "              7.32.0, this option accepts decimal values, but the actual time-\n"
 "              out will decrease in accuracy as the specified timeout increases\n"
 "              in decimal precision.  See also the --connect-timeout option.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --mail-auth <address>\n"
 "              (SMTP) Specify a single address. This will be  used  to  specify\n"
-, stdout);
- fputs(
 "              the  authentication  address  (identity)  of a submitted message\n"
 "              that is being relayed to another server.\n"
 "\n"
 "              (Added in 7.25.0)\n"
 "\n"
 "       --mail-from <address>\n"
 "              (SMTP) Specify a single address that the given mail  should  get\n"
 "              sent from.\n"
 "\n"
+, stdout);
+ fputs(
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
 "              for such files this option has no effect even if the file trans-\n"
+, stdout);
+ fputs(
 "              fer  ends  up  being larger than this given limit. This concerns\n"
 "              both FTP and HTTP transfers.\n"
 "\n"
 "       --mail-rcpt <address>\n"
+"              (SMTP) Specify a single address, user name or mailing list name.\n"
+"              When performing a mail transfer, the recipient should specify  a\n"
+"              valid email address to send the mail to. (Added in 7.20.0)\n"
+"\n"
+"              When  performing  an  address  verification  (VRFY command), the\n"
 , stdout);
  fputs(
-"              (SMTP) Specify a single address that the given mail  should  get\n"
-"              sent  to. This option can be used multiple times to specify many\n"
-"              recipients.\n"
+"              recipient should be specified as the user name or user name  and\n"
+"              domain (as per Section 3.5 of RFC5321). (Added in 7.34.0)\n"
 "\n"
-"              (Added in 7.20.0)\n"
+"              When performing a mailing list expand (EXPN command), the recip-\n"
+"              ient should be specified using the mailing list  name,  such  as\n"
+"              \"Friends\" or \"London-Office\".  (Added in 7.34.0)\n"
 "\n"
 "       --max-redirs <num>\n"
-"              Set maximum number of  redirection-followings  allowed.  If  -L,\n"
-"              --location is used, this option can be used to prevent curl from\n"
-"              following redirections \"in absurdum\". By default, the  limit  is\n"
+"              Set  maximum  number  of  redirection-followings allowed. If -L,\n"
 , stdout);
  fputs(
-"              set  to 50 redirections. Set this option to -1 to make it limit-\n"
+"              --location is used, this option can be used to prevent curl from\n"
+"              following  redirections  \"in absurdum\". By default, the limit is\n"
+"              set to 50 redirections. Set this option to -1 to make it  limit-\n"
 "              less.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --metalink\n"
-"              This option can tell curl to parse and process a  given  URI  as\n"
-"              Metalink  file  (both  version 3 and 4 (RFC 5854) are supported)\n"
-"              and make use of the mirrors listed within for failover if  there\n"
+"              This  option  can  tell curl to parse and process a given URI as\n"
 , stdout);
  fputs(
-"              are  errors (such as the file or server not being available). It\n"
-"              will also verify the hash of the file after  the  download  com-\n"
-"              pletes.  The Metalink file itself is downloaded and processed in\n"
+"              Metalink file (both version 3 and 4 (RFC  5854)  are  supported)\n"
+"              and  make use of the mirrors listed within for failover if there\n"
+"              are errors (such as the file or server not being available).  It\n"
+"              will  also  verify  the hash of the file after the download com-\n"
+"              pletes. The Metalink file itself is downloaded and processed  in\n"
 "              memory and not stored in the local file system.\n"
 "\n"
+, stdout);
+ fputs(
 "              Example to use a remote Metalink file:\n"
 "\n"
 "              curl --metalink http://www.example.com/example.metalink\n"
 "\n"
-, stdout);
- fputs(
 "              To use a Metalink file in the local file system, use FILE proto-\n"
 "              col (file://):\n"
 "\n"
 "              curl --metalink file://example.metalink\n"
 "\n"
-"              Please  note  that if FILE protocol is disabled, there is no way\n"
-"              to use a local Metalink file at the time of this  writing.  Also\n"
-"              note  that  if  --metalink  and  --include  are  used  together,\n"
-"              --include will be ignored. This is because including headers  in\n"
+"              Please note that if FILE protocol is disabled, there is  no  way\n"
+"              to  use  a local Metalink file at the time of this writing. Also\n"
 , stdout);
  fputs(
-"              the  response  will break Metalink parser and if the headers are\n"
+"              note  that  if  --metalink  and  --include  are  used  together,\n"
+"              --include  will be ignored. This is because including headers in\n"
+"              the response will break Metalink parser and if the  headers  are\n"
 "              included in the file described in Metalink file, hash check will\n"
 "              fail.\n"
 "\n"
 "              (Added in 7.27.0, if built against the libmetalink library.)\n"
 "\n"
 "       -n, --netrc\n"
-"              Makes  curl  scan  the  .netrc  (_netrc  on Windows) file in the\n"
+, stdout);
+ fputs(
+"              Makes curl scan the .netrc  (_netrc  on  Windows)  file  in  the\n"
 "              user's home directory for login name and password. This is typi-\n"
+"              cally used for FTP on UNIX. If used with HTTP, curl will  enable\n"
+"              user  authentication.  See netrc(4) or ftp(1) for details on the\n"
+"              file format. Curl will not complain if that  file  doesn't  have\n"
+"              the  right permissions (it should not be either world- or group-\n"
 , stdout);
  fputs(
-"              cally  used for FTP on UNIX. If used with HTTP, curl will enable\n"
-"              user authentication. See netrc(4) or ftp(1) for details  on  the\n"
-"              file  format.  Curl  will not complain if that file doesn't have\n"
-"              the right permissions (it should not be either world- or  group-\n"
-"              readable).  The  environment variable \"HOME\" is used to find the\n"
+"              readable). The environment variable \"HOME\" is used to  find  the\n"
 "              home directory.\n"
 "\n"
-, stdout);
- fputs(
-"              A quick and very simple example of how  to  setup  a  .netrc  to\n"
-"              allow  curl to FTP to the machine host.domain.com with user name\n"
+"              A  quick  and  very  simple  example of how to setup a .netrc to\n"
+"              allow curl to FTP to the machine host.domain.com with user  name\n"
 "              'myself' and password 'secret' should look similar to:\n"
 "\n"
 "              machine host.domain.com login myself password secret\n"
 "\n"
 "       -N, --no-buffer\n"
-"              Disables the buffering of the output stream. In normal work sit-\n"
-"              uations,  curl  will  use a standard buffered output stream that\n"
 , stdout);
  fputs(
+"              Disables the buffering of the output stream. In normal work sit-\n"
+"              uations, curl will use a standard buffered  output  stream  that\n"
 "              will have the effect that it will output the data in chunks, not\n"
-"              necessarily  exactly  when  the data arrives.  Using this option\n"
+"              necessarily exactly when the data arrives.   Using  this  option\n"
 "              will disable that buffering.\n"
 "\n"
-"              Note that this is the negated option name  documented.  You  can\n"
+"              Note  that  this  is the negated option name documented. You can\n"
 "              thus use --buffer to enforce the buffering.\n"
 "\n"
-"       --netrc-file\n"
-"              This  option  is similar to --netrc, except that you provide the\n"
 , stdout);
  fputs(
-"              path (absolute or relative) to the netrc file that  Curl  should\n"
-"              use.   You  can  only  specify one netrc file per invocation. If\n"
-"              several --netrc-file options are provided,  only  the  last  one\n"
+"       --netrc-file\n"
+"              This option is similar to --netrc, except that you  provide  the\n"
+"              path  (absolute  or relative) to the netrc file that Curl should\n"
+"              use.  You can only specify one netrc  file  per  invocation.  If\n"
+"              several  --netrc-file  options  are  provided, only the last one\n"
 "              will be used.  (Added in 7.21.5)\n"
 "\n"
-"              This  option  overrides  any use of --netrc as they are mutually\n"
+"              This option overrides any use of --netrc as  they  are  mutually\n"
+, stdout);
+ fputs(
 "              exclusive.  It will also abide by --netrc-optional if specified.\n"
 "\n"
 "       --netrc-optional\n"
-, stdout);
- fputs(
-"              Very similar to --netrc, but this option makes the .netrc  usage\n"
+"              Very  similar to --netrc, but this option makes the .netrc usage\n"
 "              optional and not mandatory as the --netrc option does.\n"
 "\n"
 "       --negotiate\n"
-"              (HTTP)  Enables  GSS-Negotiate authentication. The GSS-Negotiate\n"
+"              (HTTP) Enables GSS-Negotiate authentication.  The  GSS-Negotiate\n"
 "              method was designed by Microsoft and is used in their web appli-\n"
-"              cations.  It  is  primarily  meant  as  a  support for Kerberos5\n"
-"              authentication but may be also used along with another authenti-\n"
 , stdout);
  fputs(
+"              cations. It is  primarily  meant  as  a  support  for  Kerberos5\n"
+"              authentication but may be also used along with another authenti-\n"
 "              cation method. For more information see IETF draft draft-brezak-\n"
 "              spnego-http-04.txt.\n"
 "\n"
-"              If you want to enable Negotiate for your  proxy  authentication,\n"
+"              If  you  want to enable Negotiate for your proxy authentication,\n"
 "              then use --proxy-negotiate.\n"
 "\n"
-"              This  option  requires a library built with GSSAPI support. This\n"
-"              is not very common. Use -V, --version to  see  if  your  version\n"
-"              supports GSS-Negotiate.\n"
-"\n"
+"              This option requires a library built with GSSAPI  support.  This\n"
 , stdout);
  fputs(
-"              When  using this option, you must also provide a fake -u, --user\n"
-"              option to activate the authentication code properly.  Sending  a\n"
-"              '-u  :'  is  enough  as  the  user name and password from the -u\n"
+"              is  not  very  common.  Use -V, --version to see if your version\n"
+"              supports GSS-Negotiate.\n"
+"\n"
+"              When using this option, you must also provide a fake -u,  --user\n"
+"              option  to  activate the authentication code properly. Sending a\n"
+"              '-u :' is enough as the user  name  and  password  from  the  -u\n"
 "              option aren't actually used.\n"
 "\n"
-"              If this option is used several times,  only  the  first  one  is\n"
+"              If  this  option  is  used  several times, only the first one is\n"
 "              used.\n"
 "\n"
-"       --no-keepalive\n"
-"              Disables the use of keepalive messages on the TCP connection, as\n"
 , stdout);
  fputs(
+"       --no-keepalive\n"
+"              Disables the use of keepalive messages on the TCP connection, as\n"
 "              by default curl enables them.\n"
 "\n"
-"              Note that this is the negated option name  documented.  You  can\n"
+"              Note  that  this  is the negated option name documented. You can\n"
 "              thus use --keepalive to enforce keepalive.\n"
 "\n"
 "       --no-sessionid\n"
-"              (SSL)  Disable curl's use of SSL session-ID caching.  By default\n"
-"              all transfers are done using the cache. Note that while  nothing\n"
-"              should  ever  get  hurt  by attempting to reuse SSL session-IDs,\n"
+"              (SSL) Disable curl's use of SSL session-ID caching.  By  default\n"
+"              all  transfers are done using the cache. Note that while nothing\n"
 , stdout);
  fputs(
+"              should ever get hurt by attempting  to  reuse  SSL  session-IDs,\n"
 "              there seem to be broken SSL implementations in the wild that may\n"
-"              require  you to disable this in order for you to succeed. (Added\n"
+"              require you to disable this in order for you to succeed.  (Added\n"
 "              in 7.16.0)\n"
 "\n"
-"              Note that this is the negated option name  documented.  You  can\n"
+"              Note  that  this  is the negated option name documented. You can\n"
 "              thus use --sessionid to enforce session-ID caching.\n"
 "\n"
 "       --noproxy <no-proxy-list>\n"
-"              Comma-separated  list  of hosts which do not use a proxy, if one\n"
 , stdout);
  fputs(
-"              is specified.  The only wildcard is a single * character,  which\n"
+"              Comma-separated list of hosts which do not use a proxy,  if  one\n"
+"              is  specified.  The only wildcard is a single * character, which\n"
 "              matches all hosts, and effectively disables the proxy. Each name\n"
-"              in this list is matched as either a domain  which  contains  the\n"
-"              hostname,  or  the hostname itself. For example, local.com would\n"
-"              match  local.com,  local.com:80,  and  www.local.com,  but   not\n"
-"              www.notlocal.com.  (Added in 7.19.4).\n"
-"\n"
+"              in  this  list  is matched as either a domain which contains the\n"
+"              hostname, or the hostname itself. For example,  local.com  would\n"
+"              match   local.com,  local.com:80,  and  www.local.com,  but  not\n"
 , stdout);
  fputs(
-"       --ntlm (HTTP)  Enables  NTLM  authentication.  The  NTLM authentication\n"
+"              www.notlocal.com.  (Added in 7.19.4).\n"
+"\n"
+"       --ntlm (HTTP) Enables  NTLM  authentication.  The  NTLM  authentication\n"
 "              method was designed by Microsoft and is used by IIS web servers.\n"
-"              It  is a proprietary protocol, reverse-engineered by clever peo-\n"
+"              It is a proprietary protocol, reverse-engineered by clever  peo-\n"
 "              ple and implemented in curl based on their efforts. This kind of\n"
-"              behavior  should  not be endorsed, you should encourage everyone\n"
-"              who uses NTLM to switch to a public and  documented  authentica-\n"
+"              behavior should not be endorsed, you should  encourage  everyone\n"
 , stdout);
  fputs(
+"              who  uses  NTLM to switch to a public and documented authentica-\n"
 "              tion method instead, such as Digest.\n"
 "\n"
-"              If  you  want to enable NTLM for your proxy authentication, then\n"
+"              If you want to enable NTLM for your proxy  authentication,  then\n"
 "              use --proxy-ntlm.\n"
 "\n"
-"              This option requires a library built with SSL support.  Use  -V,\n"
+"              This  option  requires a library built with SSL support. Use -V,\n"
 "              --version to see if your curl supports NTLM.\n"
 "\n"
-"              If  this  option  is  used  several times, only the first one is\n"
+"              If this option is used several times,  only  the  first  one  is\n"
 "              used.\n"
 "\n"
-"       -o, --output <file>\n"
 , stdout);
  fputs(
+"       -o, --output <file>\n"
 "              Write output to <file> instead of stdout. If you are using {} or\n"
-"              []  to  fetch  multiple documents, you can use '#' followed by a\n"
-"              number in the <file> specifier. That variable will  be  replaced\n"
+"              [] to fetch multiple documents, you can use '#'  followed  by  a\n"
+"              number  in  the <file> specifier. That variable will be replaced\n"
 "              with the current string for the URL being fetched. Like in:\n"
 "\n"
 "                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
 "\n"
 "              or use several variables like:\n"
 "\n"
-"                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
-"\n"
 , stdout);
  fputs(
-"              You  may use this option as many times as the number of URLs you\n"
+"                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
+"\n"
+"              You may use this option as many times as the number of URLs  you\n"
 "              have.\n"
 "\n"
-"              See also the --create-dirs option to create the  local  directo-\n"
-"              ries  dynamically.  Specifying the output as '-' (a single dash)\n"
+"              See  also  the --create-dirs option to create the local directo-\n"
+"              ries dynamically. Specifying the output as '-' (a  single  dash)\n"
 "              will force the output to be done to stdout.\n"
 "\n"
 "       -O, --remote-name\n"
-"              Write output to a local file named like the remote file we  get.\n"
-"              (Only  the file part of the remote file is used, the path is cut\n"
+"              Write  output to a local file named like the remote file we get.\n"
 , stdout);
  fputs(
+"              (Only the file part of the remote file is used, the path is  cut\n"
 "              off.)\n"
 "\n"
-"              The remote file name to use for saving  is  extracted  from  the\n"
+"              The  remote  file  name  to use for saving is extracted from the\n"
 "              given URL, nothing else.\n"
 "\n"
-"              Consequentially,  the  file will be saved in the current working\n"
-"              directory. If you want the file saved in a different  directory,\n"
+"              Consequentially, the file will be saved in the  current  working\n"
+"              directory.  If you want the file saved in a different directory,\n"
 "              make sure you change current working directory before you invoke\n"
-"              curl with the -O, --remote-name flag!\n"
-"\n"
 , stdout);
  fputs(
-"              You may use this option as many times as the number of URLs  you\n"
+"              curl with the -O, --remote-name flag!\n"
+"\n"
+"              There is no URL decoding done on the file name. If it has %20 or\n"
+"              other URL encoded parts of the name, they will end up  as-is  as\n"
+"              file name.\n"
+"\n"
+"              You  may use this option as many times as the number of URLs you\n"
 "              have.\n"
 "\n"
 "       --oauth2-bearer\n"
-"              (IMAP/POP3/SMTP)  Specify  the Bearer Token for OAUTH 2.0 server\n"
-"              authentication.  The Bearer Token is used in conjuction with the\n"
-"              user  name  which  can  be specified as part of the --url or -u,\n"
+"              (IMAP, POP3, SMTP) Specify the Bearer Token for OAUTH 2.0 server\n"
+, stdout);
+ fputs(
+"              authentication. The Bearer Token is used in conjunction with the\n"
+"              user name which can be specified as part of  the  --url  or  -u,\n"
 "              --user options.\n"
 "\n"
-"              The Bearer Token and user name are formatted  according  to  RFC\n"
+"              The  Bearer  Token  and user name are formatted according to RFC\n"
 "              6750.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -p, --proxytunnel\n"
 "              When an HTTP proxy is used (-x, --proxy), this option will cause\n"
-"              non-HTTP protocols  to  attempt  to  tunnel  through  the  proxy\n"
-"              instead  of merely using it to do HTTP-like operations. The tun-\n"
-"              nel approach is made with the HTTP  proxy  CONNECT  request  and\n"
-"              requires that the proxy allows direct connect to the remote port\n"
 , stdout);
  fputs(
+"              non-HTTP  protocols  to  attempt  to  tunnel  through  the proxy\n"
+"              instead of merely using it to do HTTP-like operations. The  tun-\n"
+"              nel  approach  is  made  with the HTTP proxy CONNECT request and\n"
+"              requires that the proxy allows direct connect to the remote port\n"
 "              number curl wants to tunnel through to.\n"
 "\n"
 "       -P, --ftp-port <address>\n"
-"              (FTP) Reverses the default initiator/listener  roles  when  con-\n"
-"              necting  with  FTP.  This  switch makes curl use active mode. In\n"
-"              practice, curl then tells the server  to  connect  back  to  the\n"
-"              client's specified address and port, while passive mode asks the\n"
-"              server to setup an IP address and port for  it  to  connect  to.\n"
+"              (FTP)  Reverses  the  default initiator/listener roles when con-\n"
 , stdout);
  fputs(
+"              necting with FTP. This switch makes curl  use  active  mode.  In\n"
+"              practice,  curl  then  tells  the  server to connect back to the\n"
+"              client's specified address and port, while passive mode asks the\n"
+"              server  to  setup  an  IP address and port for it to connect to.\n"
 "              <address> should be one of:\n"
 "\n"
 "              interface\n"
-"                     i.e  \"eth0\"  to  specify which interface's IP address you\n"
+"                     i.e \"eth0\" to specify which interface's  IP  address  you\n"
+, stdout);
+ fputs(
 "                     want to use (Unix only)\n"
 "\n"
 "              IP address\n"
 "                     i.e \"192.168.10.1\" to specify the exact IP address\n"
 "\n"
 "              host name\n"
 "                     i.e \"my.host.domain\" to specify the machine\n"
 "\n"
-"              -      make curl pick the same IP address that is  already  used\n"
-, stdout);
- fputs(
+"              -      make  curl  pick the same IP address that is already used\n"
 "                     for the control connection\n"
 "\n"
-"       If  this  option is used several times, the last one will be used. Dis-\n"
-"       able the use of PORT with --ftp-pasv. Disable the attempt  to  use  the\n"
-"       EPRT  command  instead  of PORT by using --disable-eprt. EPRT is really\n"
+"       If this option is used several times, the last one will be  used.  Dis-\n"
+, stdout);
+ fputs(
+"       able  the  use  of PORT with --ftp-pasv. Disable the attempt to use the\n"
+"       EPRT command instead of PORT by using --disable-eprt.  EPRT  is  really\n"
 "       PORT++.\n"
 "\n"
 "       Starting in 7.19.5, you can append \":[start]-[end]\" to the right of the\n"
-"       address,  to tell curl what TCP port range to use. That means you spec-\n"
+"       address, to tell curl what TCP port range to use. That means you  spec-\n"
+"       ify  a  port  range,  from  a lower to a higher number. A single number\n"
+"       works as well, but do note that it increases the risk of failure  since\n"
 , stdout);
  fputs(
-"       ify a port range, from a lower to a  higher  number.  A  single  number\n"
-"       works  as well, but do note that it increases the risk of failure since\n"
 "       the port may not be available.\n"
 "\n"
 "       --pass <phrase>\n"
 "              (SSL/SSH) Passphrase for the private key\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --post301\n"
-"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
+"              (HTTP)  Tells  curl  to  respect RFC 2616/10.3.2 and not convert\n"
+"              POST requests into GET requests when following a  301  redirect-\n"
+"              ion.  The  non-RFC  behaviour  is ubiquitous in web browsers, so\n"
 , stdout);
  fputs(
-"              POST  requests  into GET requests when following a 301 redirect-\n"
-"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
-"              curl  does  the  conversion  by default to maintain consistency.\n"
+"              curl does the conversion by  default  to  maintain  consistency.\n"
 "              However, a server may require a POST to remain a POST after such\n"
-"              a  redirection.  This  option  is meaningful only when using -L,\n"
+"              a redirection. This option is meaningful  only  when  using  -L,\n"
 "              --location (Added in 7.17.1)\n"
 "\n"
 "       --post302\n"
+"              (HTTP)  Tells  curl  to  respect RFC 2616/10.3.2 and not convert\n"
+"              POST requests into GET requests when following a  302  redirect-\n"
 , stdout);
  fputs(
-"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
-"              POST  requests  into GET requests when following a 302 redirect-\n"
-"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
-"              curl  does  the  conversion  by default to maintain consistency.\n"
+"              ion.  The  non-RFC  behaviour  is ubiquitous in web browsers, so\n"
+"              curl does the conversion by  default  to  maintain  consistency.\n"
 "              However, a server may require a POST to remain a POST after such\n"
-"              a  redirection.  This  option  is meaningful only when using -L,\n"
-, stdout);
- fputs(
+"              a redirection. This option is meaningful  only  when  using  -L,\n"
 "              --location (Added in 7.19.1)\n"
 "\n"
 "       --post303\n"
-"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
-"              POST  requests  into GET requests when following a 303 redirect-\n"
-"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
-"              curl  does  the  conversion  by default to maintain consistency.\n"
-"              However, a server may require a POST to remain a POST after such\n"
+"              (HTTP)  Tells  curl  to  respect RFC 2616/10.3.2 and not convert\n"
 , stdout);
  fputs(
-"              a  redirection.  This  option  is meaningful only when using -L,\n"
+"              POST requests into GET requests when following a  303  redirect-\n"
+"              ion.  The  non-RFC  behaviour  is ubiquitous in web browsers, so\n"
+"              curl does the conversion by  default  to  maintain  consistency.\n"
+"              However, a server may require a POST to remain a POST after such\n"
+"              a redirection. This option is meaningful  only  when  using  -L,\n"
 "              --location (Added in 7.26.0)\n"
 "\n"
 "       --proto <protocols>\n"
-"              Tells  curl  to  use  the  listed  protocols  for  its   initial\n"
+, stdout);
+ fputs(
+"              Tells   curl  to  use  the  listed  protocols  for  its  initial\n"
 "              retrieval. Protocols are evaluated left to right, are comma sep-\n"
-"              arated, and are each a protocol name or 'all',  optionally  pre-\n"
+"              arated,  and  are each a protocol name or 'all', optionally pre-\n"
 "              fixed by zero or more modifiers. Available modifiers are:\n"
 "\n"
-, stdout);
- fputs(
 "              +  Permit this protocol in addition to protocols already permit-\n"
 "                 ted (this is the default if no modifier is used).\n"
 "\n"
-"              -  Deny this protocol, removing it from the  list  of  protocols\n"
+, stdout);
+ fputs(
+"              -  Deny  this  protocol,  removing it from the list of protocols\n"
 "                 already permitted.\n"
 "\n"
-"              =  Permit  only this protocol (ignoring the list already permit-\n"
-"                 ted), though subject  to  later  modification  by  subsequent\n"
+"              =  Permit only this protocol (ignoring the list already  permit-\n"
+"                 ted),  though  subject  to  later  modification by subsequent\n"
 "                 entries in the comma separated list.\n"
 "\n"
-, stdout);
- fputs(
 "              For example:\n"
 "\n"
 "              --proto -ftps  uses the default protocols, but disables ftps\n"
 "\n"
 "              --proto -all,https,+http\n"
+, stdout);
+ fputs(
 "                             only enables http and https\n"
 "\n"
 "              --proto =http,https\n"
 "                             also only enables http and https\n"
 "\n"
-"              Unknown  protocols  produce  a  warning.  This allows scripts to\n"
-"              safely rely on being able to disable potentially dangerous  pro-\n"
-, stdout);
- fputs(
-"              tocols,  without  relying  upon  support for that protocol being\n"
+"              Unknown protocols produce a  warning.  This  allows  scripts  to\n"
+"              safely  rely on being able to disable potentially dangerous pro-\n"
+"              tocols, without relying upon support  for  that  protocol  being\n"
 "              built into curl to avoid an error.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option can be used multiple times, in which case the effect\n"
-"              is  the same as concatenating the protocols into one instance of\n"
+"              is the same as concatenating the protocols into one instance  of\n"
 "              the option.\n"
 "\n"
 "              (Added in 7.20.2)\n"
 "\n"
 "       --proto-redir <protocols>\n"
-"              Tells curl to use the listed protocols  after  a  redirect.  See\n"
-, stdout);
- fputs(
+"              Tells  curl  to  use  the listed protocols after a redirect. See\n"
 "              --proto for how protocols are represented.\n"
 "\n"
 "              (Added in 7.20.2)\n"
 "\n"
 "       --proxy-anyauth\n"
-"              Tells  curl to pick a suitable authentication method when commu-\n"
-"              nicating with  the  given  proxy.  This  might  cause  an  extra\n"
+, stdout);
+ fputs(
+"              Tells curl to pick a suitable authentication method when  commu-\n"
+"              nicating  with  the  given  proxy.  This  might  cause  an extra\n"
 "              request/response round-trip. (Added in 7.13.2)\n"
 "\n"
 "       --proxy-basic\n"
-"              Tells  curl  to use HTTP Basic authentication when communicating\n"
+"              Tells curl to use HTTP Basic authentication  when  communicating\n"
+"              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
+"              remote host. Basic is the  default  authentication  method  curl\n"
 , stdout);
  fputs(
-"              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
-"              remote  host.  Basic  is  the default authentication method curl\n"
 "              uses with proxies.\n"
 "\n"
 "       --proxy-digest\n"
-"              Tells curl to use HTTP Digest authentication when  communicating\n"
+"              Tells  curl to use HTTP Digest authentication when communicating\n"
 "              with the given proxy. Use --digest for enabling HTTP Digest with\n"
 "              a remote host.\n"
 "\n"
 "       --proxy-negotiate\n"
-, stdout);
- fputs(
 "              Tells curl to use HTTP Negotiate authentication when communicat-\n"
-"              ing  with  the  given  proxy.  Use --negotiate for enabling HTTP\n"
+"              ing with the given proxy.  Use  --negotiate  for  enabling  HTTP\n"
 "              Negotiate with a remote host. (Added in 7.17.1)\n"
 "\n"
+, stdout);
+ fputs(
 "       --proxy-ntlm\n"
-"              Tells curl to use HTTP NTLM  authentication  when  communicating\n"
+"              Tells  curl  to  use HTTP NTLM authentication when communicating\n"
 "              with the given proxy. Use --ntlm for enabling NTLM with a remote\n"
 "              host.\n"
 "\n"
 "       --proxy1.0 <proxyhost[:port]>\n"
-, stdout);
- fputs(
-"              Use the specified HTTP 1.0 proxy. If  the  port  number  is  not\n"
+"              Use  the  specified  HTTP  1.0  proxy. If the port number is not\n"
 "              specified, it is assumed at port 1080.\n"
 "\n"
-"              The  only difference between this and the HTTP proxy option (-x,\n"
+"              The only difference between this and the HTTP proxy option  (-x,\n"
+, stdout);
+ fputs(
 "              --proxy), is that attempts to use CONNECT through the proxy will\n"
 "              specify an HTTP 1.0 protocol instead of the default HTTP 1.1.\n"
 "\n"
 "       --pubkey <key>\n"
-"              (SSH)  Public  key  file name. Allows you to provide your public\n"
-, stdout);
- fputs(
+"              (SSH) Public key file name. Allows you to  provide  your  public\n"
 "              key in this separate file.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-"       -q     If used as the first parameter on the command line,  the  curlrc\n"
-"              config  file will not be read and used. See the -K, --config for\n"
+"       -q     If  used  as the first parameter on the command line, the curlrc\n"
+, stdout);
+ fputs(
+"              config file will not be read and used. See the -K, --config  for\n"
 "              details on the default config file search path.\n"
 "\n"
 "       -Q, --quote <command>\n"
-"              (FTP/SFTP) Send an arbitrary command to the remote FTP  or  SFTP\n"
-, stdout);
- fputs(
-"              server.  Quote commands are sent BEFORE the transfer takes place\n"
-"              (just after the initial PWD command in an FTP  transfer,  to  be\n"
+"              (FTP/SFTP)  Send  an arbitrary command to the remote FTP or SFTP\n"
+"              server. Quote commands are sent BEFORE the transfer takes  place\n"
+"              (just  after  the  initial PWD command in an FTP transfer, to be\n"
 "              exact). To make commands take place after a successful transfer,\n"
-"              prefix them with a dash '-'.  To make  commands  be  sent  after\n"
-"              curl has changed the working directory, just before the transfer\n"
-"              command(s), prefix the command with a '+'  (this  is  only  sup-\n"
 , stdout);
  fputs(
-"              ported  for FTP). You may specify any number of commands. If the\n"
+"              prefix  them  with  a  dash '-'.  To make commands be sent after\n"
+"              curl has changed the working directory, just before the transfer\n"
+"              command(s),  prefix  the  command  with a '+' (this is only sup-\n"
+"              ported for FTP). You may specify any number of commands. If  the\n"
 "              server returns failure for one of the commands, the entire oper-\n"
-"              ation  will  be aborted. You must send syntactically correct FTP\n"
-"              commands as RFC 959 defines to FTP servers, or one of  the  com-\n"
-"              mands  listed  below  to  SFTP servers.  This option can be used\n"
-"              multiple times. When speaking to an FTP server, prefix the  com-\n"
+"              ation will be aborted. You must send syntactically  correct  FTP\n"
 , stdout);
  fputs(
+"              commands  as  RFC 959 defines to FTP servers, or one of the com-\n"
+"              mands listed below to SFTP servers.  This  option  can  be  used\n"
+"              multiple  times. When speaking to an FTP server, prefix the com-\n"
 "              mand with an asterisk (*) to make curl continue even if the com-\n"
 "              mand fails as by default curl will stop at first failure.\n"
 "\n"
-"              SFTP is a binary protocol. Unlike for FTP, curl interprets  SFTP\n"
-"              quote  commands  itself before sending them to the server.  File\n"
+"              SFTP  is a binary protocol. Unlike for FTP, curl interprets SFTP\n"
+, stdout);
+ fputs(
+"              quote commands itself before sending them to the  server.   File\n"
 "              names may be quoted shell-style to embed spaces or special char-\n"
-"              acters.   Following is the list of all supported SFTP quote com-\n"
+"              acters.  Following is the list of all supported SFTP quote  com-\n"
 "              mands:\n"
 "\n"
+"              chgrp group file\n"
+"                     The  chgrp command sets the group ID of the file named by\n"
+"                     the file operand to the group ID specified by  the  group\n"
 , stdout);
  fputs(
-"              chgrp group file\n"
-"                     The chgrp command sets the group ID of the file named  by\n"
-"                     the  file  operand to the group ID specified by the group\n"
 "                     operand. The group operand is a decimal integer group ID.\n"
 "\n"
 "              chmod mode file\n"
-"                     The chmod command modifies the  file  mode  bits  of  the\n"
+"                     The  chmod  command  modifies  the  file mode bits of the\n"
 "                     specified file. The mode operand is an octal integer mode\n"
 "                     number.\n"
 "\n"
-, stdout);
- fputs(
 "              chown user file\n"
 "                     The chown command sets the owner of the file named by the\n"
-"                     file  operand  to the user ID specified by the user oper-\n"
+"                     file operand to the user ID specified by the  user  oper-\n"
+, stdout);
+ fputs(
 "                     and. The user operand is a decimal integer user ID.\n"
 "\n"
 "              ln source_file target_file\n"
 "                     The ln and symlink commands create a symbolic link at the\n"
-"                     target_file  location  pointing  to the source_file loca-\n"
+"                     target_file location pointing to  the  source_file  loca-\n"
 "                     tion.\n"
 "\n"
-, stdout);
- fputs(
 "              mkdir directory_name\n"
-"                     The mkdir command creates  the  directory  named  by  the\n"
+"                     The  mkdir  command  creates  the  directory named by the\n"
 "                     directory_name operand.\n"
 "\n"
+, stdout);
+ fputs(
 "              pwd    The pwd command returns the absolute pathname of the cur-\n"
 "                     rent working directory.\n"
 "\n"
 "              rename source target\n"
 "                     The rename command renames the file or directory named by\n"
-"                     the  source  operand to the destination path named by the\n"
-, stdout);
- fputs(
+"                     the source operand to the destination path named  by  the\n"
 "                     target operand.\n"
 "\n"
 "              rm file\n"
 "                     The rm command removes the file specified by the file op-\n"
 "                     erand.\n"
 "\n"
+, stdout);
+ fputs(
 "              rmdir directory\n"
-"                     The  rmdir  command removes the directory entry specified\n"
+"                     The rmdir command removes the directory  entry  specified\n"
 "                     by the directory operand, provided it is empty.\n"
 "\n"
 "              symlink source_file target_file\n"
 "                     See ln.\n"
 "\n"
 "       -r, --range <range>\n"
-, stdout);
- fputs(
-"              (HTTP/FTP/SFTP/FILE) Retrieve a byte range (i.e a partial  docu-\n"
-"              ment)  from  a  HTTP/1.1,  FTP  or  SFTP server or a local FILE.\n"
+"              (HTTP/FTP/SFTP/FILE)  Retrieve a byte range (i.e a partial docu-\n"
+"              ment) from a HTTP/1.1, FTP or  SFTP  server  or  a  local  FILE.\n"
 "              Ranges can be specified in a number of ways.\n"
 "\n"
+, stdout);
+ fputs(
 "              0-499     specifies the first 500 bytes\n"
 "\n"
 "              500-999   specifies the second 500 bytes\n"
 "\n"
 "              -500      specifies the last 500 bytes\n"
 "\n"
 "              9500-     specifies the bytes from offset 9500 and forward\n"
 "\n"
-, stdout);
- fputs(
 "              0-0,-1    specifies the first and last byte only(*)(H)\n"
 "\n"
 "              500-700,600-799\n"
 "                        specifies 300 bytes from offset 500(H)\n"
 "\n"
 "              100-199,500-599\n"
+, stdout);
+ fputs(
 "                        specifies two separate 100-byte ranges(*)(H)\n"
 "\n"
-"       (*) = NOTE that this will cause the server to reply  with  a  multipart\n"
+"       (*)  =  NOTE  that this will cause the server to reply with a multipart\n"
 "       response!\n"
 "\n"
-"       Only  digit characters (0-9) are valid in the 'start' and 'stop' fields\n"
-, stdout);
- fputs(
-"       of the 'start-stop' range syntax. If a non-digit character is given  in\n"
-"       the  range, the server's response will be unspecified, depending on the\n"
+"       Only digit characters (0-9) are valid in the 'start' and 'stop'  fields\n"
+"       of  the 'start-stop' range syntax. If a non-digit character is given in\n"
+"       the range, the server's response will be unspecified, depending on  the\n"
 "       server's configuration.\n"
 "\n"
-"       You should also be aware that many HTTP/1.1 servers do  not  have  this\n"
-"       feature  enabled,  so  that  when  you  attempt  to get a range, you'll\n"
-"       instead get the whole document.\n"
-"\n"
-"       FTP and SFTP range downloads only support the simple 'start-stop'  syn-\n"
 , stdout);
  fputs(
-"       tax  (optionally  with  one of the numbers omitted). FTP use depends on\n"
+"       You  should  also  be aware that many HTTP/1.1 servers do not have this\n"
+"       feature enabled, so that when  you  attempt  to  get  a  range,  you'll\n"
+"       instead get the whole document.\n"
+"\n"
+"       FTP  and SFTP range downloads only support the simple 'start-stop' syn-\n"
+"       tax (optionally with one of the numbers omitted). FTP  use  depends  on\n"
 "       the extended FTP command SIZE.\n"
 "\n"
 "       If this option is used several times, the last one will be used.\n"
 "\n"
 "       -R, --remote-time\n"
-"              When used, this will make curl attempt to figure out  the  time-\n"
-"              stamp  of  the  remote  file,  and if that is available make the\n"
+, stdout);
+ fputs(
+"              When  used,  this will make curl attempt to figure out the time-\n"
+"              stamp of the remote file, and if  that  is  available  make  the\n"
 "              local file get that same timestamp.\n"
 "\n"
 "       --random-file <file>\n"
-, stdout);
- fputs(
 "              (SSL) Specify the path name to file containing what will be con-\n"
-"              sidered  as  random  data.  The  data is used to seed the random\n"
+"              sidered as random data. The data is  used  to  seed  the  random\n"
 "              engine for SSL connections.  See also the --egd-file option.\n"
 "\n"
+, stdout);
+ fputs(
 "       --raw  (HTTP) When used, it disables all internal HTTP decoding of con-\n"
-"              tent  or  transfer  encodings  and  instead makes them passed on\n"
+"              tent or transfer encodings and  instead  makes  them  passed  on\n"
 "              unaltered, raw. (Added in 7.16.2)\n"
 "\n"
 "       --remote-name-all\n"
-, stdout);
- fputs(
-"              This option changes the default action for all given URLs to  be\n"
+"              This  option changes the default action for all given URLs to be\n"
 "              dealt with as if -O, --remote-name were used for each one. So if\n"
 "              you want to disable that for a specific URL after --remote-name-\n"
-"              all  has  been  used,  you  must use \"-o -\" or --no-remote-name.\n"
+, stdout);
+ fputs(
+"              all has been used, you must  use  \"-o  -\"  or  --no-remote-name.\n"
 "              (Added in 7.19.0)\n"
 "\n"
 "       --resolve <host:port:address>\n"
-"              Provide a custom address for a  specific  host  and  port  pair.\n"
-, stdout);
- fputs(
-"              Using  this,  you  can make the curl requests(s) use a specified\n"
-"              address and prevent the otherwise normally resolved  address  to\n"
-"              be  used.  Consider it a sort of /etc/hosts alternative provided\n"
-"              on the command line. The port number should be the  number  used\n"
-"              for  the  specific  protocol the host will be used for. It means\n"
-"              you need several entries if you want to provide address for  the\n"
+"              Provide  a  custom  address  for  a specific host and port pair.\n"
+"              Using this, you can make the curl requests(s)  use  a  specified\n"
+"              address  and  prevent the otherwise normally resolved address to\n"
+"              be used. Consider it a sort of /etc/hosts  alternative  provided\n"
 , stdout);
  fputs(
+"              on  the  command line. The port number should be the number used\n"
+"              for the specific protocol the host will be used  for.  It  means\n"
+"              you  need several entries if you want to provide address for the\n"
 "              same host but different ports.\n"
 "\n"
-"              This  option  can  be  used many times to add many host names to\n"
+"              This option can be used many times to add  many  host  names  to\n"
 "              resolve.\n"
 "\n"
 "              (Added in 7.21.3)\n"
 "\n"
 "       --retry <num>\n"
-"              If a transient error is returned when curl tries  to  perform  a\n"
-"              transfer,  it  will retry this number of times before giving up.\n"
-"              Setting the number to 0 makes curl do no retries (which  is  the\n"
 , stdout);
  fputs(
-"              default).  Transient  error  means either: a timeout, an FTP 4xx\n"
+"              If  a  transient  error is returned when curl tries to perform a\n"
+"              transfer, it will retry this number of times before  giving  up.\n"
+"              Setting  the  number to 0 makes curl do no retries (which is the\n"
+"              default). Transient error means either: a timeout,  an  FTP  4xx\n"
 "              response code or an HTTP 5xx response code.\n"
 "\n"
-"              When curl is about to retry a transfer, it will first  wait  one\n"
-"              second  and  then for all forthcoming retries it will double the\n"
-"              waiting time until it reaches 10 minutes which then will be  the\n"
-"              delay  between  the rest of the retries.  By using --retry-delay\n"
+"              When  curl  is about to retry a transfer, it will first wait one\n"
 , stdout);
  fputs(
-"              you  disable  this  exponential  backoff  algorithm.  See   also\n"
-"              --retry-max-time  to  limit  the total time allowed for retries.\n"
+"              second and then for all forthcoming retries it will  double  the\n"
+"              waiting  time until it reaches 10 minutes which then will be the\n"
+"              delay between the rest of the retries.  By  using  --retry-delay\n"
+"              you   disable  this  exponential  backoff  algorithm.  See  also\n"
+"              --retry-max-time to limit the total time  allowed  for  retries.\n"
 "              (Added in 7.12.3)\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --retry-delay <seconds>\n"
-"              Make curl sleep this amount of time before  each  retry  when  a\n"
-"              transfer  has  failed  with  a  transient  error (it changes the\n"
+"              Make  curl  sleep  this  amount of time before each retry when a\n"
+"              transfer has failed with  a  transient  error  (it  changes  the\n"
+"              default  backoff time algorithm between retries). This option is\n"
+"              only interesting if --retry is also used. Setting this delay  to\n"
 , stdout);
  fputs(
-"              default backoff time algorithm between retries). This option  is\n"
-"              only  interesting if --retry is also used. Setting this delay to\n"
-"              zero will make curl use the default  backoff  time.   (Added  in\n"
+"              zero  will  make  curl  use the default backoff time.  (Added in\n"
 "              7.12.3)\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --retry-max-time <seconds>\n"
-"              The  retry  timer  is  reset  before the first transfer attempt.\n"
-, stdout);
- fputs(
+"              The retry timer is reset  before  the  first  transfer  attempt.\n"
 "              Retries will be done as usual (see --retry) as long as the timer\n"
 "              hasn't reached this given limit. Notice that if the timer hasn't\n"
-"              reached the limit, the request will be made and  while  perform-\n"
-"              ing,  it may take longer than this given time period. To limit a\n"
-"              single request's maximum time, use  -m,  --max-time.   Set  this\n"
-"              option to zero to not timeout retries. (Added in 7.12.3)\n"
-"\n"
 , stdout);
  fputs(
+"              reached  the  limit, the request will be made and while perform-\n"
+"              ing, it may take longer than this given time period. To limit  a\n"
+"              single  request's  maximum  time,  use -m, --max-time.  Set this\n"
+"              option to zero to not timeout retries. (Added in 7.12.3)\n"
+"\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -s, --silent\n"
-"              Silent  or  quiet  mode. Don't show progress meter or error mes-\n"
-"              sages.  Makes Curl mute. It will still output the data  you  ask\n"
+"              Silent or quiet mode. Don't show progress meter  or  error  mes-\n"
+, stdout);
+ fputs(
+"              sages.   Makes  Curl mute. It will still output the data you ask\n"
 "              for, potentially even to the terminal/stdout unless you redirect\n"
 "              it.\n"
 "\n"
 "       --sasl-ir\n"
-"              Enable initial  response  in  SASL  authentication.   (Added  in\n"
+"              Enable  initial  response  in  SASL  authentication.   (Added in\n"
 "              7.31.0)\n"
 "\n"
 "       -S, --show-error\n"
-, stdout);
- fputs(
-"              When  used  with  -s  it  makes curl show an error message if it\n"
+"              When used with -s it makes curl show  an  error  message  if  it\n"
 "              fails.\n"
 "\n"
-"       --ssl  (FTP, POP3, IMAP, SMTP) Try to use SSL/TLS for  the  connection.\n"
+"       --ssl  (FTP,  POP3,  IMAP, SMTP) Try to use SSL/TLS for the connection.\n"
+, stdout);
+ fputs(
 "              Reverts to a non-secure connection if the server doesn't support\n"
-"              SSL/TLS.  See also --ftp-ssl-control and --ssl-reqd for  differ-\n"
+"              SSL/TLS.   See also --ftp-ssl-control and --ssl-reqd for differ-\n"
 "              ent levels of encryption required. (Added in 7.20.0)\n"
 "\n"
-"              This  option  was formerly known as --ftp-ssl (Added in 7.11.0).\n"
-, stdout);
- fputs(
-"              That option name can still be used but  will  be  removed  in  a\n"
+"              This option was formerly known as --ftp-ssl (Added  in  7.11.0).\n"
+"              That  option  name  can  still  be used but will be removed in a\n"
 "              future version.\n"
 "\n"
 "       --ssl-reqd\n"
-"              (FTP,  POP3,  IMAP,  SMTP)  Require  SSL/TLS for the connection.\n"
+, stdout);
+ fputs(
+"              (FTP, POP3, IMAP, SMTP)  Require  SSL/TLS  for  the  connection.\n"
 "              Terminates the connection if the server doesn't support SSL/TLS.\n"
 "              (Added in 7.20.0)\n"
 "\n"
-"              This  option  was  formerly  known  as  --ftp-ssl-reqd (added in\n"
-"              7.15.5). That option name can still be used but will be  removed\n"
-, stdout);
- fputs(
+"              This option was  formerly  known  as  --ftp-ssl-reqd  (added  in\n"
+"              7.15.5).  That option name can still be used but will be removed\n"
 "              in a future version.\n"
 "\n"
 "       --ssl-allow-beast\n"
-"              (SSL)  This option tells curl to not work around a security flaw\n"
-"              in the SSL3 and TLS1.0 protocols known as BEAST.  If this option\n"
-"              isn't  used,  the  SSL layer may use work-arounds known to cause\n"
-"              interoperability problems with some older  SSL  implementations.\n"
-"              WARNING: this option loosens the SSL security, and by using this\n"
+"              (SSL) This option tells curl to not work around a security  flaw\n"
 , stdout);
  fputs(
+"              in the SSL3 and TLS1.0 protocols known as BEAST.  If this option\n"
+"              isn't used, the SSL layer may use work-arounds  known  to  cause\n"
+"              interoperability  problems  with some older SSL implementations.\n"
+"              WARNING: this option loosens the SSL security, and by using this\n"
 "              flag you ask for exactly that.  (Added in 7.25.0)\n"
 "\n"
 "       --socks4 <host[:port]>\n"
 "              Use the specified SOCKS4 proxy. If the port number is not speci-\n"
+, stdout);
+ fputs(
 "              fied, it is assumed at port 1080. (Added in 7.15.2)\n"
 "\n"
-"              This  option  overrides any previous use of -x, --proxy, as they\n"
+"              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
-, stdout);
- fputs(
 "              socks4 proxy with -x, --proxy using a socks4:// protocol prefix.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks4a <host[:port]>\n"
+, stdout);
+ fputs(
 "              Use the specified SOCKS4a proxy. If the port number is not spec-\n"
 "              ified, it is assumed at port 1080. (Added in 7.18.0)\n"
 "\n"
-"              This option overrides any previous use of -x, --proxy,  as  they\n"
+"              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
-, stdout);
- fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
-"              socks4a proxy with -x, --proxy using a socks4a:// protocol  pre-\n"
+"              socks4a  proxy with -x, --proxy using a socks4a:// protocol pre-\n"
 "              fix.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --socks5-hostname <host[:port]>\n"
-"              Use  the  specified  SOCKS5 proxy (and let the proxy resolve the\n"
-"              host name). If the port number is not specified, it  is  assumed\n"
-, stdout);
- fputs(
+"              Use the specified SOCKS5 proxy (and let the  proxy  resolve  the\n"
+"              host  name).  If the port number is not specified, it is assumed\n"
 "              at port 1080. (Added in 7.18.0)\n"
 "\n"
-"              This  option  overrides any previous use of -x, --proxy, as they\n"
+"              This option overrides any previous use of -x, --proxy,  as  they\n"
 "              are mutually exclusive.\n"
 "\n"
+, stdout);
+ fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 hostname proxy with -x, --proxy using a socks5h:// proto-\n"
 "              col prefix.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
-, stdout);
- fputs(
-"              (This  option  was  previously  wrongly  documented  and used as\n"
+"              (This option was  previously  wrongly  documented  and  used  as\n"
 "              --socks without the number appended.)\n"
 "\n"
 "       --socks5 <host[:port]>\n"
-"              Use the specified SOCKS5 proxy  -  but  resolve  the  host  name\n"
-"              locally.  If  the port number is not specified, it is assumed at\n"
+, stdout);
+ fputs(
+"              Use  the  specified  SOCKS5  proxy  -  but resolve the host name\n"
+"              locally. If the port number is not specified, it is  assumed  at\n"
 "              port 1080.\n"
 "\n"
-"              This option overrides any previous use of -x, --proxy,  as  they\n"
+"              This  option  overrides any previous use of -x, --proxy, as they\n"
 "              are mutually exclusive.\n"
 "\n"
-, stdout);
- fputs(
 "              Since 7.21.7, this option is superfluous since you can specify a\n"
 "              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
-"              (This  option  was  previously  wrongly  documented  and used as\n"
+"              (This option was  previously  wrongly  documented  and  used  as\n"
 "              --socks without the number appended.)\n"
 "\n"
-"              This option (as well as --socks4) does not work with IPV6,  FTPS\n"
+"              This  option (as well as --socks4) does not work with IPV6, FTPS\n"
 "              or LDAP.\n"
 "\n"
-, stdout);
- fputs(
 "       --socks5-gssapi-service <servicename>\n"
 "              The default service name for a socks server is rcmd/server-fqdn.\n"
 "              This option allows you to change it.\n"
 "\n"
-"              Examples:  --socks5  proxy-name  --socks5-gssapi-service   sockd\n"
-"              would  use sockd/proxy-name --socks5 proxy-name --socks5-gssapi-\n"
-"              service sockd/real-name  would  use  sockd/real-name  for  cases\n"
-"              where  the proxy-name does not match the principal name.  (Added\n"
 , stdout);
  fputs(
+"              Examples:   --socks5  proxy-name  --socks5-gssapi-service  sockd\n"
+"              would use sockd/proxy-name --socks5 proxy-name  --socks5-gssapi-\n"
+"              service  sockd/real-name  would  use  sockd/real-name  for cases\n"
+"              where the proxy-name does not match the principal name.   (Added\n"
 "              in 7.19.4).\n"
 "\n"
 "       --socks5-gssapi-nec\n"
-"              As part of the gssapi negotiation a protection mode  is  negoti-\n"
-"              ated.  RFC  1961 says in section 4.3/4.4 it should be protected,\n"
-"              but the NEC  reference  implementation  does  not.   The  option\n"
-"              --socks5-gssapi-nec  allows the unprotected exchange of the pro-\n"
+"              As  part  of the gssapi negotiation a protection mode is negoti-\n"
+, stdout);
+ fputs(
+"              ated. RFC 1961 says in section 4.3/4.4 it should  be  protected,\n"
+"              but  the  NEC  reference  implementation  does  not.  The option\n"
+"              --socks5-gssapi-nec allows the unprotected exchange of the  pro-\n"
 "              tection mode negotiation. (Added in 7.19.4).\n"
 "\n"
 "       --stderr <file>\n"
-, stdout);
- fputs(
-"              Redirect all writes to stderr to the specified file instead.  If\n"
+"              Redirect  all writes to stderr to the specified file instead. If\n"
 "              the file name is a plain '-', it is instead written to stdout.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -t, --telnet-option <OPT=val>\n"
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
 "       -T, --upload-file <file>\n"
-"              This  transfers  the  specified local file to the remote URL. If\n"
+"              This transfers the specified local file to the  remote  URL.  If\n"
+, stdout);
+ fputs(
 "              there is no file part in the specified URL, Curl will append the\n"
 "              local file name. NOTE that you must use a trailing / on the last\n"
-"              directory to really prove to Curl that there is no file name  or\n"
+"              directory  to really prove to Curl that there is no file name or\n"
 "              curl will think that your last directory name is the remote file\n"
-, stdout);
- fputs(
 "              name to use. That will most likely cause the upload operation to\n"
 "              fail. If this is used on an HTTP(S) server, the PUT command will\n"
 "              be used.\n"
 "\n"
-"              Use the file name \"-\" (a single dash) to use stdin instead of  a\n"
-"              given  file.   Alternately,  the file name \".\" (a single period)\n"
-"              may be specified instead of \"-\" to  use  stdin  in  non-blocking\n"
-"              mode  to  allow  reading  server  output  while  stdin  is being\n"
 , stdout);
  fputs(
+"              Use  the file name \"-\" (a single dash) to use stdin instead of a\n"
+"              given file.  Alternately, the file name \".\"  (a  single  period)\n"
+"              may  be  specified  instead  of \"-\" to use stdin in non-blocking\n"
+"              mode to  allow  reading  server  output  while  stdin  is  being\n"
 "              uploaded.\n"
 "\n"
 "              You can specify one -T for each URL on the command line. Each -T\n"
+, stdout);
+ fputs(
 "              + URL pair specifies what to upload and to where. curl also sup-\n"
 "              ports \"globbing\" of the -T argument, meaning that you can upload\n"
-"              multiple  files  to  a single URL by using the same URL globbing\n"
+"              multiple files to a single URL by using the  same  URL  globbing\n"
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
 "       --tcp-nodelay\n"
-"              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
+, stdout);
+ fputs(
+"              Turn  on the TCP_NODELAY option. See the curl_easy_setopt(3) man\n"
 "              page for details about this option. (Added in 7.11.2)\n"
 "\n"
 "       --tftp-blksize <value>\n"
 "              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
 "              size that curl will try to use when transferring data to or from\n"
 "              a TFTP server. By default 512 bytes will be used.\n"
 "\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+, stdout);
+ fputs(
 "              (Added in 7.20.0)\n"
 "\n"
 "       --tlsauthtype <authtype>\n"
-"              Set  TLS  authentication  type.  Currently,  the  only supported\n"
-"              option is \"SRP\",  for  TLS-SRP  (RFC  5054).  If  --tlsuser  and\n"
-"              --tlspassword  are specified but --tlsauthtype is not, then this\n"
+"              Set TLS  authentication  type.  Currently,  the  only  supported\n"
+"              option  is  \"SRP\",  for  TLS-SRP  (RFC  5054).  If --tlsuser and\n"
+"              --tlspassword are specified but --tlsauthtype is not, then  this\n"
 "              option defaults to \"SRP\".  (Added in 7.21.4)\n"
 "\n"
-"       --tlsuser <user>\n"
+"       --tlspassword <password>\n"
+"              Set  password  for use with the TLS authentication method speci-\n"
 , stdout);
  fputs(
-"              Set username for use with the TLS authentication  method  speci-\n"
-"              fied  with  --tlsauthtype.  Requires  that --tlspassword also be\n"
+"              fied with --tlsauthtype. Requires that --tlsuser  also  be  set.\n"
+"              (Added in 7.21.4)\n"
+"\n"
+"       --tlsuser <user>\n"
+"              Set  username  for use with the TLS authentication method speci-\n"
+"              fied with --tlsauthtype. Requires  that  --tlspassword  also  be\n"
 "              set.  (Added in 7.21.4)\n"
 "\n"
-"       --tlspassword <password>\n"
-"              Set password for use with the TLS authentication  method  speci-\n"
-"              fied  with  --tlsauthtype.  Requires that --tlsuser also be set.\n"
-"              (Added in 7.21.4)\n"
+"       --tlsv1.0\n"
+"              (SSL) Forces curl to use TLS version 1.0 when negotiating with a\n"
+"              remote TLS server.  (Added in 7.34.0)\n"
 "\n"
-"       --tr-encoding\n"
+"       --tlsv1.1\n"
 , stdout);
  fputs(
+"              (SSL) Forces curl to use TLS version 1.1 when negotiating with a\n"
+"              remote TLS server.  (Added in 7.34.0)\n"
+"\n"
+"       --tlsv1.2\n"
+"              (SSL) Forces curl to use TLS version 1.2 when negotiating with a\n"
+"              remote TLS server.  (Added in 7.34.0)\n"
+"\n"
+"       --tr-encoding\n"
 "              (HTTP) Request a compressed Transfer-Encoding response using one\n"
 "              of  the  algorithms curl supports, and uncompress the data while\n"
 "              receiving it.\n"
 "\n"
+, stdout);
+ fputs(
 "              (Added in 7.21.6)\n"
 "\n"
 "       --trace <file>\n"
 "              Enables a full trace dump of all  incoming  and  outgoing  data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
-, stdout);
- fputs(
 "              This option overrides previous uses of -v, --verbose or --trace-\n"
 "              ascii.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-ascii <file>\n"
+, stdout);
+ fputs(
 "              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
 "              including descriptive information, to the given output file. Use\n"
 "              \"-\" as filename to have the output sent to stdout.\n"
 "\n"
-, stdout);
- fputs(
 "              This is very similar to --trace, but leaves out the hex part and\n"
 "              only shows the ASCII part of the dump. It makes  smaller  output\n"
 "              that might be easier to read for untrained humans.\n"
 "\n"
+, stdout);
+ fputs(
 "              This option overrides previous uses of -v, --verbose or --trace.\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --trace-time\n"
 "              Prepends  a  time  stamp to each trace or verbose line that curl\n"
-, stdout);
- fputs(
 "              displays.  (Added in 7.14.0)\n"
 "\n"
 "       -u, --user <user:password;options>\n"
 "              Specify the user name, password and optional  login  options  to\n"
+, stdout);
+ fputs(
 "              use   for  server  authentication.  Overrides  -n,  --netrc  and\n"
 "              --netrc-optional.\n"
 "\n"
 "              If you simply specify the user name, with or without  the  login\n"
 "              options, curl will prompt for a password.\n"
 "\n"
 "              If  you use an SSPI-enabled curl binary and perform NTLM authen-\n"
-, stdout);
- fputs(
 "              tication, you can force curl to select the user name  and  pass-\n"
 "              word  from  your environment by simply specifying a single colon\n"
+, stdout);
+ fputs(
 "              with this option: \"-u :\" or by specfying the  login  options  on\n"
 "              their own, for example \"-u ;auth=NTLM\".\n"
 "\n"
 "              You  can use the optional login options part to specify protocol\n"
 "              specific options that may  be  used  during  authentication.  At\n"
-, stdout);
- fputs(
 "              present  only  IMAP, POP3 and SMTP support login options as part\n"
 "              of the user login information. For more  information  about  the\n"
+, stdout);
+ fputs(
 "              login  options  please  see  RFC  2384,  RFC 5092 and IETF draft\n"
 "              draft-earhart-url-smtp-00.txt (Added in 7.31.0).\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -U, --proxy-user <user:password>\n"
 "              Specify the user name and password to use for proxy  authentica-\n"
-, stdout);
- fputs(
 "              tion.\n"
 "\n"
 "              If  you  use an SSPI-enabled curl binary and do NTLM authentica-\n"
+, stdout);
+ fputs(
 "              tion, you can force curl to pick up the user name  and  password\n"
 "              from  your  environment by simply specifying a single colon with\n"
 "              this option: \"-U :\".\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --url <URL>\n"
 "              Specify a URL to fetch. This option is  mostly  handy  when  you\n"
-, stdout);
- fputs(
 "              want to specify URL(s) in a config file.\n"
 "\n"
+, stdout);
+ fputs(
 "              This  option  may  be used any number of times. To control where\n"
 "              this URL is written, use the -o, --output or the  -O,  --remote-\n"
 "              name options.\n"
 "       -v, --verbose\n"
 "              Makes  the  fetching  more  verbose/talkative. Mostly useful for\n"
 "              debugging. A line starting with '>' means \"header data\" sent  by\n"
