fputs(
"  The default way for curl is to issue the PASV command which causes the\n"
"  server to open another port and await another connection performed by the\n"
"  client. This is good if the client is behind a firewall that don't allow\n"
"  incoming connections.\n"
"\n"
"        curl ftp.download.com\n"
"\n"
"  If the server for example, is behind a firewall that don't allow connections\n"
"  on other ports than 21 (or if it just doesn't support the PASV command), the\n"
, stdout);