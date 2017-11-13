fputs(
"\n"
"  Example on how to automatically retrieve a document using a certificate with\n"
"  a personal password:\n"
"\n"
"        curl -E /path/to/cert.pem:password https://secure.site.com/\n"
"\n"
"  If you neglect to specify the password on the command line, you will be\n"
"  prompted for the correct password before any data can be received.\n"
"\n"
"  Many older SSL-servers have problems with SSLv3 or TLS, which newer versions\n"
"  of OpenSSL etc use, therefore it is sometimes useful to specify what\n"
, stdout);