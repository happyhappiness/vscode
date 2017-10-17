fputs(
"              socks5 hostname proxy with -x, --proxy using a socks5h:// proto-\n"
"              col prefix.\n"
"\n"
"              Since 7.52.0, --preproxy can be used to specify a SOCKS proxy at\n"
"              the same time -x, --proxy is used with an HTTP/HTTPS  proxy.  In\n"
"              such a case curl first connects to the SOCKS proxy and then con-\n"
"              nects (through SOCKS) to the HTTP or HTTPS proxy.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
, stdout);