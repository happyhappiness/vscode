fputs(
"       server's configuration.\n"
"\n"
"       You  should  also  be aware that many HTTP/1.1 servers do not have this\n"
"       feature enabled, so that when  you  attempt  to  get  a  range,  you'll\n"
"       instead get the whole document.\n"
"\n"
"       FTP  and SFTP range downloads only support the simple 'start-stop' syn-\n"
"       tax (optionally with one of the numbers omitted). FTP  use  depends  on\n"
"       the extended FTP command SIZE.\n"
"\n"
"       If this option is used several times, the last one will be used.\n"
"\n"
, stdout);