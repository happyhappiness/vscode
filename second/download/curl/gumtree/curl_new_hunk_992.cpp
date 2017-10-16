"\n"
"              If  no  '=' symbol is used in the line, it is treated as a file-\n"
"              name to use to read previously stored cookie lines  from,  which\n"
, stdout);
 fputs(
"              should  be used in this session if they match. Using this method\n"
"              also activates the cookie engine which  will  make  curl  record\n"
"              incoming cookies too, which may be handy if you're using this in\n"
"              combination with the -L, --location option. The file  format  of\n"
"              the  file  to  read cookies from should be plain HTTP headers or\n"
"              the Netscape/Mozilla cookie file format.\n"
"\n"
, stdout);
 fputs(
"              The file specified with -b, --cookie is only used as  input.  No\n"
"              cookies  will  be written to the file. To store cookies, use the\n"
"              -c, --cookie-jar option.\n"
"\n"
"              Exercise caution if you  are  using  this  option  and  multiple\n"
"              transfers may occur.  If you use the NAME1=VALUE1; format, or in\n"
"              a file use the Set-Cookie format and  don't  specify  a  domain,\n"
, stdout);
 fputs(
"              then the cookie is sent for any domain (even after redirects are\n"
"              followed) and cannot be modified by a server-set cookie. If  the\n"
"              cookie  engine is enabled and a server sets a cookie of the same\n"
"              name then both will be sent on a future transfer to that server,\n"
"              likely  not  what  you  intended.  To address these issues set a\n"
"              domain in Set-Cookie (doing that will  include  sub-domains)  or\n"
, stdout);
 fputs(
"              use the Netscape format.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -B, --use-ascii\n"
"              (FTP/LDAP)  Enable  ASCII  transfer.  For  FTP, this can also be\n"
"              enforced by using an URL that ends with \";type=A\".  This  option\n"
"              causes data sent to stdout to be in text mode for win32 systems.\n"
"\n"
"       --basic\n"
"              (HTTP)  Tells  curl  to  use  HTTP Basic authentication with the\n"
, stdout);
 fputs(
"              remote host. This is the default  and  this  option  is  usually\n"
"              pointless, unless you use it to override a previously set option\n"
"              that sets a different authentication  method  (such  as  --ntlm,\n"
"              --digest, or --negotiate).\n"
"\n"
"              Used together with -u, --user and -x, --proxy.\n"
"\n"
"              See also --proxy-basic.\n"
"\n"
"       -c, --cookie-jar <file name>\n"
"              (HTTP)  Specify to which file you want curl to write all cookies\n"
, stdout);
 fputs(
"              after a completed operation. Curl writes all cookies  previously\n"
"              read  from a specified file as well as all cookies received from\n"
"              remote server(s). If no cookies are known, no data will be writ-\n"
"              ten.  The  file  will  be written using the Netscape cookie file\n"
"              format. If you set the file name to  a  single  dash,  \"-\",  the\n"
"              cookies will be written to stdout.\n"
"\n"
, stdout);
 fputs(
"              This  command  line  option will activate the cookie engine that\n"
"              makes curl record and use cookies. Another way to activate it is\n"
"              to use the -b, --cookie option.\n"
"\n"
"              If the cookie jar can't be created or written to, the whole curl\n"
"              operation won't fail or even report an error clearly.  Using  -v\n"
"              will get a warning displayed, but that is the only visible feed-\n"
, stdout);
 fputs(
"              back you get about this possibly lethal situation.\n"
"\n"
"              Since 7.43.0 cookies that were imported in the Set-Cookie format\n"
"              without a domain name are not exported by this option.\n"
"\n"
"              If  this  option  is used several times, the last specified file\n"
"              name will be used.\n"
"\n"
"       -C, --continue-at <offset>\n"
"              Continue/Resume a previous file transfer at  the  given  offset.\n"
, stdout);
