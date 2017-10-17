fputs(
"              Since 7.21.7, this option is superfluous since you can specify a\n"
"              socks5 proxy with -x, --proxy using a socks5:// protocol prefix.\n"
"              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
"              the same time -x, --proxy is used with an HTTP/HTTPS  proxy.  In\n"
"              such a case curl first connects to the SOCKS proxy and then con-\n"
"              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
"\n"
, stdout);