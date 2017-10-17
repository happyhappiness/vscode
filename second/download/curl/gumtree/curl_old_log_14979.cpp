fputs(
"  The FTP protocol requires one of the involved parties to open a second\n"
"  connection as soon as data is about to get transferred. There are two ways to\n"
"  do this.\n"
"\n"
"  The default way for curl is to issue the PASV command which causes the\n"
"  server to open another port and await another connection performed by the\n"
"  client. This is good if the client is behind a firewall that doesn't allow\n"
"  incoming connections.\n"
"\n"
"        curl ftp.download.com\n"
"\n"
, stdout);