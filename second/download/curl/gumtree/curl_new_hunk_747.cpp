"              However, a server may require a POST to remain a POST after such\n"
, stdout);
 fputs(
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.19.1)\n"
"\n"
"       --post303\n"
"              (HTTP) Tells curl to respect RFC  2616/10.3.2  and  not  convert\n"
"              POST  requests  into GET requests when following a 303 redirect-\n"
"              ion. The non-RFC behaviour is ubiquitous  in  web  browsers,  so\n"
"              curl  does  the  conversion  by default to maintain consistency.\n"
, stdout);
 fputs(
"              However, a server may require a POST to remain a POST after such\n"
"              a  redirection.  This  option  is meaningful only when using -L,\n"
"              --location (Added in 7.26.0)\n"
"\n"
"       --proto <protocols>\n"
"              Tells  curl  to  use  the  listed  protocols  for  its   initial\n"
"              retrieval. Protocols are evaluated left to right, are comma sep-\n"
"              arated, and are each a protocol name or 'all',  optionally  pre-\n"
, stdout);
 fputs(
"              fixed by zero or more modifiers. Available modifiers are:\n"
"\n"
"              +  Permit this protocol in addition to protocols already permit-\n"
"                 ted (this is the default if no modifier is used).\n"
"\n"
"              -  Deny this protocol, removing it from the  list  of  protocols\n"
"                 already permitted.\n"
"\n"
"              =  Permit  only this protocol (ignoring the list already permit-\n"
"                 ted), though subject  to  later  modification  by  subsequent\n"
, stdout);
 fputs(
"                 entries in the comma separated list.\n"
"\n"
"              For example:\n"
"\n"
"              --proto -ftps  uses the default protocols, but disables ftps\n"
"\n"
"              --proto -all,https,+http\n"
"                             only enables http and https\n"
"\n"
"              --proto =http,https\n"
"                             also only enables http and https\n"
"\n"
"              Unknown  protocols  produce  a  warning.  This allows scripts to\n"
, stdout);
 fputs(
"              safely rely on being able to disable potentially dangerous  pro-\n"
"              tocols,  without  relying  upon  support for that protocol being\n"
"              built into curl to avoid an error.\n"
"\n"
"              This option can be used multiple times, in which case the effect\n"
"              is  the same as concatenating the protocols into one instance of\n"
"              the option.\n"
"\n"
"              (Added in 7.20.2)\n"
"\n"
"       --proto-redir <protocols>\n"
, stdout);
 fputs(
"              Tells curl to use the listed protocols  after  a  redirect.  See\n"
"              --proto for how protocols are represented.\n"
"\n"
"              (Added in 7.20.2)\n"
"\n"
"       --proxy-anyauth\n"
"              Tells  curl to pick a suitable authentication method when commu-\n"
"              nicating with  the  given  proxy.  This  might  cause  an  extra\n"
"              request/response round-trip. (Added in 7.13.2)\n"
"\n"
"       --proxy-basic\n"
, stdout);
 fputs(
"              Tells  curl  to use HTTP Basic authentication when communicating\n"
"              with the given proxy. Use --basic for enabling HTTP Basic with a\n"
"              remote  host.  Basic  is  the default authentication method curl\n"
"              uses with proxies.\n"
"\n"
"       --proxy-digest\n"
"              Tells curl to use HTTP Digest authentication when  communicating\n"
"              with the given proxy. Use --digest for enabling HTTP Digest with\n"
"              a remote host.\n"
"\n"
, stdout);
 fputs(
"       --proxy-negotiate\n"
"              Tells curl to use HTTP Negotiate authentication when communicat-\n"
"              ing  with  the  given  proxy.  Use --negotiate for enabling HTTP\n"
"              Negotiate with a remote host. (Added in 7.17.1)\n"
"\n"
"       --proxy-ntlm\n"
"              Tells curl to use HTTP NTLM  authentication  when  communicating\n"
