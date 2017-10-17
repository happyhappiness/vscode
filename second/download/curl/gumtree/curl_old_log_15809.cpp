fputs(
"              option overrides -F, --form and -I, --head and --upload.\n"
"\n"
"       --delegation <LEVEL>\n"
"              (GSS/kerberos) Set LEVEL to tell the server what it  is  allowed\n"
"              to delegate when it comes to user credentials.\n"
"\n"
"              none   Don't allow any delegation.\n"
"\n"
"              policy Delegates  if  and only if the OK-AS-DELEGATE flag is set\n"
"                     in the Kerberos service ticket,  which  is  a  matter  of\n"
"                     realm policy.\n"
"\n"
, stdout);