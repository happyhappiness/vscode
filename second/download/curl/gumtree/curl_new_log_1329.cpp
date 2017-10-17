fputs(
"        curl ftp.download.com\n"
"\n"
"  If the server for example, is behind a firewall that don't allow connections\n"
"  on other ports than 21 (or if it just doesn't support the PASV command), the\n"
"  other way to do it is to use the PORT command and instruct the server to\n"
"  connect to the client on the given (as parameters to the PORT command) IP\n"
"  number and port.\n"
"\n"
"  The -P flag to curl supports a few different options. Your machine may have\n"
, stdout);