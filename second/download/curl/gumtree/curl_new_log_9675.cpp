fputs(
"  SSL-version curl should use. Use -3, -2 or -1 to specify that exact SSL\n"
"  version to use (for SSLv3, SSLv2 or TLSv1 respectively):\n"
"\n"
"        curl -2 https://secure.site.com/\n"
"\n"
"  Otherwise, curl will first attempt to use v3 and then v2.\n"
"\n"
"  To use OpenSSL to convert your favourite browser's certificate into a PEM\n"
"  formatted one that curl can use, do something like this:\n"
"\n"
"    In Netscape, you start with hitting the 'Security' menu button.\n"
"\n"
, stdout);