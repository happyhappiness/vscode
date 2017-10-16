"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       --post301\n"
, stdout);
 fputs(
"              Tells  curl  to  respect  RFC  2616/10.3.2  and not convert POST\n"
"              requests into GET requests when following a 301 redirection. The\n"
"              non-RFC  behaviour  is  ubiquitous in web browsers, so curl does\n"
"              the conversion by default to maintain  consistency.  However,  a\n"
"              server  may  require  a POST to remain a POST after such a redi-\n"
"              rection. This option is meaningful only when using  -L,  --loca-\n"
, stdout);
 fputs(
"              tion (Added in 7.17.1)\n"
"\n"
"       --post302\n"
"              Tells  curl  to  respect  RFC  2616/10.3.2  and not convert POST\n"
"              requests into GET requests when following a 302 redirection. The\n"
"              non-RFC  behaviour  is  ubiquitous in web browsers, so curl does\n"
"              the conversion by default to maintain  consistency.  However,  a\n"
"              server  may  require  a POST to remain a POST after such a redi-\n"
, stdout);
 fputs(
"              rection. This option is meaningful only when using  -L,  --loca-\n"
"              tion (Added in 7.19.1)\n"
"\n"
"       --proto <protocols>\n"
"              Tells   curl  to  use  the  listed  protocols  for  its  initial\n"
"              retrieval. Protocols are evaluated left to right, are comma sep-\n"
"              arated,  and  are each a protocol name or 'all', optionally pre-\n"
"              fixed by zero or more modifiers. Available modifiers are:\n"
