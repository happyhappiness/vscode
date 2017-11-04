fputs(
"              override a previous -P/-ftp-port option. (Added in 7.11.0)\n"
"\n"
"              If  this  option  is  used  several times, only the first one is\n"
"              used. Undoing an enforced passive really isn't  doable  but  you\n"
"              must then instead enforce the correct -P, --ftp-port again.\n"
"\n"
"              Passive mode means that curl will try the EPSV command first and\n"
"              then PASV, unless --disable-epsv is used.\n"
"\n"
"       --ftp-skip-pasv-ip\n"
, stdout);