 "              curl --metalink file://example.metalink\n"
 "\n"
 "              Please note that if FILE protocol is disabled, there is  no  way\n"
 "              to  use  a local Metalink file at the time of this writing. Also\n"
 , stdout);
  fputs(
-"              note  that  If  --metalink  and  --include  are  used  together,\n"
+"              note  that  if  --metalink  and  --include  are  used  together,\n"
 "              --include  will be ignored. This is because including headers in\n"
 "              the response will break Metalink parser and if the  headers  are\n"
 "              included in the file described in Metalink file, hash check will\n"
 "              fail.\n"
 "\n"
 "              (Added in 7.27.0, if built against the libmetalink library.)\n"
