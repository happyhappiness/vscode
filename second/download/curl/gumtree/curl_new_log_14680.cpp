fputs(
"              --include will be ignored. This is because including headers  in\n"
"              the  response  will break Metalink parser and if the headers are\n"
"              included in the file described in Metalink file, hash check will\n"
"              fail.\n"
"\n"
"              --metalink  requires  that  the  underlying libcurl was built to\n"
"              support metalink. Added in 7.27.0.\n"
"\n"
"       --negotiate\n"
"              (HTTP) Enables Negotiate (SPNEGO) authentication.\n"
"\n"
, stdout);