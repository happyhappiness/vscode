fputs(
"       You  should  also  be aware that many HTTP/1.1 servers do not have this\n"
"       feature enabled, so that when  you  attempt  to  get  a  range,  you'll\n"
"       instead get the whole document.\n"
"\n"
"       FTP  range  downloads  only  support  the  simple  syntax  'start-stop'\n"
"       (optionally with one of the numbers omitted). It depends on the non-RFC\n"
"       command SIZE.\n"
"\n"
"       If this option is used several times, the last one will be used.\n"
"\n"
, stdout);