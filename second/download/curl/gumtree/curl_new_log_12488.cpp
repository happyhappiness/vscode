fputs(
"              Set  TLS  authentication  type.  Currently,  the  only supported\n"
"              option is \"SRP\",  for  TLS-SRP  (RFC  5054).  If  --tlsuser  and\n"
"              --tlspassword  are specified but --tlsauthtype is not, then this\n"
"              option defaults to \"SRP\".  (Added in 7.21.4)\n"
"\n"
"       --tlspassword <password>\n"
"              Set password for use with the TLS authentication  method  speci-\n"
"              fied  with  --tlsauthtype.  Requires that --tlsuser also be set.\n"
, stdout);