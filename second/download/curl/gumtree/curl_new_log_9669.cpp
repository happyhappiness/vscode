fputs(
"  client. This is good if the client is behind a firewall that doesn't allow\n"
"  incoming connections.\n"
"\n"
"        curl ftp.download.com\n"
"\n"
"  If the server, for example, is behind a firewall that doesn't allow connections\n"
"  on ports other than 21 (or if it just doesn't support the PASV command), the\n"
"  other way to do it is to use the PORT command and instruct the server to\n"
"  connect to the client on the given IP number and port (as parameters to the\n"
"  PORT command).\n"
"\n"
, stdout);