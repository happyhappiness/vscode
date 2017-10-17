fputs(
"       FTP  range  downloads  only  support  the  simple  syntax  'start-stop'\n"
"       (optionally with one of the numbers omitted). It depends on the non-RFC\n"
"       command SIZE.\n"
"\n"
"       If this option is used several times, the last one will be used.\n"
"\n"
"       -R/--remote-time\n"
"              When used, this will make libcurl  attempt  to  figure  out  the\n"
"              timestamp  of the remote file, and if that is available make the\n"
"              local file get that same timestamp.\n"
"\n"
, stdout);