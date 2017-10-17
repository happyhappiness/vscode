fputs(
"       See also --tlsv1.0 and --tlsv1.1 and --tlsv1.2. --tls-max requires that\n"
"       the underlying libcurl was built to support TLS. Added in 7.54.0.\n"
"\n"
"       --tlsauthtype <type>\n"
"              Set TLS  authentication  type.  Currently,  the  only  supported\n"
"              option  is  \"SRP\",  for  TLS-SRP  (RFC  5054).  If --tlsuser and\n"
"              --tlspassword are specified but --tlsauthtype is not, then  this\n"
"              option defaults to \"SRP\".\n"
"\n"
"              Added in 7.21.4.\n"
"\n"
, stdout);