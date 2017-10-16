fputs(
"       -u/--user <user:password>\n"
"              Specify user and password  to  use  for  server  authentication.\n"
"              Overrides -n/--netrc and --netrc-optional.\n"
"\n"
"              If  you  use  an SSPI-enabled curl binary and do NTLM autentica-\n"
"              tion, you can force curl to pick up the user name  and  password\n"
"              from  your  environment by simply specifying a single colon with\n"
"              this option: \"-u :\".\n"
"\n"
, stdout);