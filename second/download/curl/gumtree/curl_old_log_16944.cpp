puts(
"  prompted for the correct password before any data can be received.\n"
"\n"
"  Many older SSL-servers have problems with SSLv3 or TLS, that newer versions\n"
"  of OpenSSL etc is using, therefore it is sometimes useful to specify what\n"
"  SSL-version curl should use. Use -3 or -2 to specify that exact SSL version\n"
"  to use:\n"
"\n"
"        curl -2 https://secure.site.com/\n"
"\n"
"  Otherwise, curl will first attempt to use v3 and then v2.\n"
"\n"
"  To use OpenSSL to convert your favourite browser's certificate into a PEM\n"
);