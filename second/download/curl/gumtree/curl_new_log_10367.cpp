fputs(
"              POST  requests  into GET requests when following a 302 redirect-\n"
"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
"              curl  does  the  conversion  by default to maintain consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.19.1)\n"
"\n"
"       --post303\n"
, stdout);