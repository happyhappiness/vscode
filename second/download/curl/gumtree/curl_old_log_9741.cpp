fputs(
"       --dns-interface <interface>\n"
"              Tell curl to send outgoing  DNS  requests  through  <interface>.\n"
"              This  option  is  a  counterpart  to --interface (which does not\n"
"              affect DNS). The supplied string must be an interface name  (not\n"
"              an address).\n"
"\n"
"              This  option  requires  that  libcurl  was built with a resolver\n"
"              backend that supports this operation. The c-ares backend is  the\n"
, stdout);