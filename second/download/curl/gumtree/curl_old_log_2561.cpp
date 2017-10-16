fputs(
"              already uses for the control connection. (Added in 7.14.2)\n"
"\n"
"              This option has no effect if PORT, EPRT or EPSV is used  instead\n"
"              of PASV.\n"
"\n"
"              If  this  option  is  used  twice, the second will again use the\n"
"              server's suggested address.\n"
"\n"
"       --ftp-ssl\n"
"              (FTP) Try to use SSL/TLS for the FTP connection.  Reverts  to  a\n"
"              non-secure  connection  if  the  server doesn't support SSL/TLS.\n"
, stdout);