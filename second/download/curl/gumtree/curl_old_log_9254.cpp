fputs(
"              Please note that if FILE protocol is disabled, there is  no  way\n"
"              to  use  a local Metalink file at the time of this writing. Also\n"
"              note  that  if  --metalink  and  --include  are  used  together,\n"
"              --include  will be ignored. This is because including headers in\n"
"              the response will break Metalink parser and if the  headers  are\n"
"              included in the file described in Metalink file, hash check will\n"
"              fail.\n"
"\n"
, stdout);