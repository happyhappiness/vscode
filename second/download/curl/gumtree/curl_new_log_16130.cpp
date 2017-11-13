fputs(
"              to a asterisk '*' only, it matches all hosts.\n"
"\n"
"              Since 7.53.0, this environment variable disable the  proxy  even\n"
"              if  specify  -x,  --proxy  option. That is NO_PROXY=direct.exam-\n"
"              ple.com  curl  -x  http://proxy.example.com  http://direct.exam-\n"
"              ple.com     accesses    the    target    URL    directly,    and\n"
"              NO_PROXY=direct.example.com  curl  -x   http://proxy.example.com\n"
, stdout);