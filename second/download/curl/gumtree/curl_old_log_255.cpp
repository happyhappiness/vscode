puts(
"  client. This is good if the client is behind a firewall that don't allow\n"
"  incoming connections.\n"
"\n"
"        curl ftp.download.com\n"
"\n"
"  If the server for example, is behind a firewall that don't allow connections\n"
"  on other ports than 21 (or if it just doesn't support the PASV command), the\n"
"  other way to do it is to use the PORT command and instruct the server to\n"
"  connect to the client on the given (as parameters to the PORT command) IP\n"
"  number and port.\n"
"\n"
);