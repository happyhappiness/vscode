fputs(
"              (SSL)  Tells  curl  to use false start during the TLS handshake.\n"
"              False start is a mode where a  TLS  client  will  start  sending\n"
"              application data before verifying the server's Finished message,\n"
"              thus saving a round trip when performing a full handshake.\n"
"\n"
"              This is currently only implemented in the NSS and Secure  Trans-\n"
"              port  (on  iOS  7.0  or  later, or OS X 10.9 or later) backends.\n"
, stdout);