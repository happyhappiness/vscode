fputs(
"        curl -u user:passwd -x my-proxy:888 http://www.get.this/\n"
"\n"
" Some proxies require special authentication. Specify by using -U as above:\n"
"\n"
"        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
"\n"
" A comma-separated list of hosts and domains which do not use the proxy can\n"
" be specified as:\n"
"\n"
"        curl --noproxy localhost,get.this -x my-proxy:888 http://www.get.this/\n"
"\n"
" If the proxy is specified with --proxy1.0 instead of --proxy or -x, then\n"
, stdout);