"              URL  path.  Normally curl will squash or merge them according to\n"
"              standards but with this option set you tell it not to do that.\n"
"\n"
"              (Added in 7.42.0)\n"
"\n"
"       --post301\n"
"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
"              POST  requests  into GET requests when following a 301 redirect-\n"
"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
, stdout);
 fputs(
"              curl  does  the  conversion  by default to maintain consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.17.1)\n"
"\n"
"       --post302\n"
"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
"              POST  requests  into GET requests when following a 302 redirect-\n"
, stdout);
 fputs(
"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
"              curl  does  the  conversion  by default to maintain consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.19.1)\n"
"\n"
"       --post303\n"
"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
, stdout);
 fputs(
"              POST  requests  into GET requests when following a 303 redirect-\n"
"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
"              curl  does  the  conversion  by default to maintain consistency.\n"
"              However, a server may require a POST to remain a POST after such\n"
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.26.0)\n"
"\n"
"       --proto <protocols>\n"
, stdout);
 fputs(
"              Tells  curl  to  use  the  listed  protocols  for  its   initial\n"
"              retrieval. Protocols are evaluated left to right, are comma sep-\n"
