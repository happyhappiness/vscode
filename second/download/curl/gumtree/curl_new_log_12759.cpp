fputs(
"              When  negotiating  a  TLS  or SSL connection, the server sends a\n"
"              certificate indicating its identity. A public key  is  extracted\n"
"              from  this certificate and if it does not exactly match the pub-\n"
"              lic key provided to this option, curl will abort the  connection\n"
"              before sending or receiving any data.\n"
"\n"
"              PEM/DER support:\n"
"                7.39.0: OpenSSL, GnuTLS and GSKit\n"
"                7.43.0: NSS and wolfSSL/CyaSSL\n"
, stdout);