fputs(
"              override a previous -P/-ftp-port option. (Added in 7.11.0)\n"
"\n"
"              If this option is used several times, the following  occurrences\n"
"              make  no  difference.  Undoing  an enforced passive really isn't\n"
"              doable but you must then instead enforce the correct -P,  --ftp-\n"
"              port again.\n"
"\n"
"              Passive mode means that curl will try the EPSV command first and\n"
"              then PASV, unless --disable-epsv is used.\n"
"\n"
"       --ftp-skip-pasv-ip\n"
, stdout);