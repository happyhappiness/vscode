fputs(
"  Pass options to the telnet protocol negotiation, by using the -t option. To\n"
"  tell the server we use a vt100 terminal, try something like:\n"
"\n"
"        curl -tTTYPE=vt100 telnet://remote.server.com\n"
"\n"
"  Other interesting options for it -t include:\n"
"\n"
"   - XDISPLOC=<X display> Sets the X display location.\n"
"\n"
"   - NEW_ENV=<var,val> Sets an environment variable.\n"
"\n"
"  NOTE: The telnet protocol does not specify any way to login with a specified\n"
, stdout);