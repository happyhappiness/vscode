fputs(
"              (HTTP) Tells curl to respect RFC 7231/6.4.2 and not convert POST\n"
"              requests into GET requests when following a 301 redirection. The\n"
"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
"              the  conversion  by  default to maintain consistency. However, a\n"
"              server may require a POST to remain a POST after  such  a  redi-\n"
"              rection.  This  option is meaningful only when using -L, --loca-\n"
"              tion.\n"
"\n"
, stdout);