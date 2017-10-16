 "              The proxy host can be specified the exact same way as the  proxy\n"
 "              environment  variables,  including the protocol prefix (http://)\n"
 , stdout);
  fputs(
 "              and the embedded user + password.\n"
 "\n"
-"              From 7.21.7, the proxy string may be  specified  with  a  proto-\n"
-"              col://  prefix  to  specify  alternative  proxy  protocols.  Use\n"
-"              socks4://, socks4a://, socks5:// or socks5h://  to  request  the\n"
-"              specific  SOCKS  version  to  be  used.  No  protocol specified,\n"
-"              http:// and all others will be treated as HTTP proxies.\n"
-"\n"
-, stdout);
- fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -X, --request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
 "              ing  with  the  HTTP server.  The specified request will be used\n"
 "              instead of the method otherwise used (which  defaults  to  GET).\n"
