fputs(
"  A comma-separated list of host names that shouldn't go through any proxy is\n"
"  set in (only an asterisk, '*' matches all hosts)\n"
"\n"
"        NO_PROXY\n"
"\n"
"  If the host name matches one of these strings, or the host is within the\n"
"  domain of one of these strings, transactions with that node will not be\n"
"  proxied. When a domain is used, it needs to start with a period. A user can\n"
"  specify that both www.example.com and foo.example.com should not uses a\n"
, stdout);