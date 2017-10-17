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