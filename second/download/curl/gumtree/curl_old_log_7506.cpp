fputs(
"  If you neglect to specify the password on the command line, you will be\n"
"  prompted for the correct password before any data can be received.\n"
"\n"
"  Many older SSL-servers have problems with SSLv3 or TLS, that newer versions\n"
"  of OpenSSL etc is using, therefore it is sometimes useful to specify what\n"
"  SSL-version curl should use. Use -3, -2 or -1 to specify that exact SSL\n"
"  version to use (for SSLv3, SSLv2 or TLSv1 respectively):\n"
"\n"
"        curl -2 https://secure.site.com/\n"
"\n"
, stdout);