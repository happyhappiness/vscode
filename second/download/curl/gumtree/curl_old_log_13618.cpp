fputs(
"              requests into GET requests when following a 301 redirection. The\n"
"              non-RFC behaviour is ubiquitous in web browsers,  so  curl  does\n"
"              the  conversion  by  default to maintain consistency. However, a\n"
"              server may require a POST to remain a POST after  such  a  redi-\n"
"              rection.  This  option is meaningful only when using -L, --loca-\n"
"              tion (Added in 7.17.1)\n"
"\n"
"       --post302\n"
, stdout);