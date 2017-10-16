"              URL  path.  Normally curl will squash or merge them according to\n"
"              standards but with this option set you tell it not to do that.\n"
"\n"
"              (Added in 7.42.0)\n"
"\n"
"       --post301\n"
"              (HTTP) Tells curl to respect RFC 7230/6.4.2 and not convert POST\n"
"              requests into GET requests when following a 301 redirection. The\n"
"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
, stdout);
 fputs(
"              the  conversion  by  default to maintain consistency. However, a\n"
"              server may require a POST to remain a POST after  such  a  redi-\n"
"              rection.  This  option is meaningful only when using -L, --loca-\n"
"              tion (Added in 7.17.1)\n"
"\n"
"       --post302\n"
"              (HTTP) Tells curl to respect RFC 7230/6.4.3 and not convert POST\n"
"              requests into GET requests when following a 302 redirection. The\n"
, stdout);
 fputs(
"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
"              the  conversion  by  default to maintain consistency. However, a\n"
"              server may require a POST to remain a POST after  such  a  redi-\n"
"              rection.  This  option is meaningful only when using -L, --loca-\n"
"              tion (Added in 7.19.1)\n"
"\n"
"       --post303\n"
"              (HTTP) Tells curl to respect RFC 7230/6.4.4 and not convert POST\n"
, stdout);
 fputs(
"              requests into GET requests when following a 303 redirection. The\n"
"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
"              the  conversion  by  default to maintain consistency. However, a\n"
"              server may require a POST to remain a POST after  such  a  redi-\n"
"              rection.  This  option is meaningful only when using -L, --loca-\n"
"              tion (Added in 7.26.0)\n"
"\n"
"       --proto <protocols>\n"
, stdout);
 fputs(
"              Tells  curl  to  use  the  listed  protocols  for  its   initial\n"
"              retrieval. Protocols are evaluated left to right, are comma sep-\n"
