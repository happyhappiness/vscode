fputs(
"              To use a Metalink file in the local file system, use FILE proto-\n"
"              col (file://):\n"
"\n"
"              curl --metalink file://example.metalink\n"
"\n"
"              Please  note  that if FILE protocol is disabled, there is no way\n"
"              to use a local Metalink file at the time of this  writing.  Also\n"
"              note  that  if  --metalink  and  --include  are  used  together,\n"
"              --include will be ignored. This is because including headers  in\n"
, stdout);