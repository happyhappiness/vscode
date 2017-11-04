fputs(
"        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
"\n"
" A comma-separated list of hosts and domains which do not use the proxy can\n"
" be specified as:\n"
"\n"
"        curl --noproxy localhost,get.this -x my-proxy:888 http://www.get.this/\n"
"\n"
" If the proxy is specified with --proxy1.0 instead of --proxy or -x, then\n"
" curl will use HTTP/1.0 instead of HTTP/1.1 for any CONNECT attempts.\n"
"\n"
" curl also supports SOCKS4 and SOCKS5 proxies with --socks4 and --socks5.\n"
"\n"
, stdout);