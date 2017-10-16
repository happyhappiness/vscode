"       The environment variables can be specified in lower case or upper case.\n"
, stdout);
 fputs(
"       The lower case version has precedence. http_proxy is an exception as it\n"
"       is only available in lower case.\n"
"\n"
"       Using an environment variable to set the proxy has the same  effect  as\n"
"       using the -x, --proxy option.\n"
"\n"
"       http_proxy [protocol://]<host>[:port]\n"
"              Sets the proxy server to use for HTTP.\n"
"       HTTPS_PROXY [protocol://]<host>[:port]\n"
"              Sets the proxy server to use for HTTPS.\n"
"\n"
"       [url-protocol]_PROXY [protocol://]<host>[:port]\n"
, stdout);
 fputs(
"              Sets  the proxy server to use for [url-protocol], where the pro-\n"
"              tocol is a protocol that curl supports and  as  specified  in  a\n"
"              URL. FTP, FTPS, POP3, IMAP, SMTP, LDAP etc.\n"
"\n"
"       ALL_PROXY [protocol://]<host>[:port]\n"
"              Sets  the  proxy  server to use if no protocol-specific proxy is\n"
"              set.\n"
"\n"
"       NO_PROXY <comma-separated list of hosts>\n"
"              list of host names that shouldn't go through any proxy.  If  set\n"
, stdout);
 fputs(
"              to a asterisk '*' only, it matches all hosts.\n"
"\n"
"              Since  7.53.0,  this environment variable disable the proxy even\n"
"              if specify -x, --proxy  option.  That  is  NO_PROXY=direct.exam-\n"
"              ple.com  curl  -x  http://proxy.example.com  http://direct.exam-\n"
"              ple.com    accesses    the    target    URL    directly,     and\n"
"              NO_PROXY=direct.example.com   curl  -x  http://proxy.example.com\n"
, stdout);
 fputs(
"              http://somewhere.example.com accesses  the  target  URL  through\n"
"              proxy.\n"
"\n"
"PROXY PROTOCOL PREFIXES\n"
"       Since  curl  version  7.21.7,  the proxy string may be specified with a\n"
"       protocol:// prefix to specify alternative proxy protocols.\n"
"\n"
"       If no protocol is specified in  the  proxy  string  or  if  the  string\n"
"       doesn't  match  a  supported  one, the proxy will be treated as an HTTP\n"
"       proxy.\n"
"\n"
, stdout);
 fputs(
"       The supported proxy protocol prefixes are as follows:\n"
"\n"
