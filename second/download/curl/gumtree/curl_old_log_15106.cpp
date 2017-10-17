fputs(
"       --ftp-pret\n"
"              (FTP) Tell curl to send a PRET command before PASV  (and  EPSV).\n"
"              Certain  FTP  servers,  mainly drftpd, require this non-standard\n"
"              command for directory listings as well as up  and  downloads  in\n"
"              PASV mode.\n"
"\n"
"              Added in 7.20.0.\n"
"\n"
"       --ftp-skip-pasv-ip\n"
"              (FTP) Tell curl to not use the IP address the server suggests in\n"
"              its response to curl's PASV command when curl connects the  data\n"
, stdout);