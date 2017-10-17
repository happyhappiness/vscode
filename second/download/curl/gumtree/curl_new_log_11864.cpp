fputs(
"              used. Undoing an enforced passive really isn't  doable  but  you\n"
"              must then instead enforce the correct -P, --ftp-port again.\n"
"\n"
"              Passive mode means that curl will try the EPSV command first and\n"
"              then PASV, unless --disable-epsv is used.\n"
"\n"
"       --ftp-skip-pasv-ip\n"
"              (FTP) Tell curl to not use the IP address the server suggests in\n"
"              its  response to curl's PASV command when curl connects the data\n"
, stdout);