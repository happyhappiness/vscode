fputs(
"              successful response codes will  slip  through,  especially  when\n"
"              authentication is involved (response codes 401 and 407).\n"
"\n"
"       --false-start\n"
"              (TLS)  Tells  curl  to use false start during the TLS handshake.\n"
"              False start is a mode where a  TLS  client  will  start  sending\n"
"              application data before verifying the server's Finished message,\n"
"              thus saving a round trip when performing a full handshake.\n"
"\n"
, stdout);