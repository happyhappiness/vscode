"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       --post301\n"
, stdout);
 fputs(
"              (HTTP)  Tells  curl  to  respect RFC 2616/10.3.2 and not convert\n"
"              POST requests into GET requests when following a  301  redirect-\n"
"              ion.  The  non-RFC  behaviour  is ubiquitous in web browsers, so\n"
"              curl does the conversion by  default  to  maintain  consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
"              a redirection. This option is meaningful  only  when  using  -L,\n"
, stdout);
 fputs(
"              --location (Added in 7.17.1)\n"
"\n"
"       --post302\n"
"              (HTTP)  Tells  curl  to  respect RFC 2616/10.3.2 and not convert\n"
"              POST requests into GET requests when following a  302  redirect-\n"
"              ion.  The  non-RFC  behaviour  is ubiquitous in web browsers, so\n"
"              curl does the conversion by  default  to  maintain  consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
, stdout);
 fputs(
"              a redirection. This option is meaningful  only  when  using  -L,\n"
"              --location (Added in 7.19.1)\n"
"\n"
"       --proto <protocols>\n"
"              Tells   curl  to  use  the  listed  protocols  for  its  initial\n"
"              retrieval. Protocols are evaluated left to right, are comma sep-\n"
"              arated,  and  are each a protocol name or 'all', optionally pre-\n"
"              fixed by zero or more modifiers. Available modifiers are:\n"
