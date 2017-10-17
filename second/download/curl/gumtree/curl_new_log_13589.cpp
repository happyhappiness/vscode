fputs(
"   - XDISPLOC=<X display> Sets the X display location.\n"
"\n"
"   - NEW_ENV=<var,val> Sets an environment variable.\n"
"\n"
"  NOTE: The telnet protocol does not specify any way to login with a specified\n"
"  user and password so curl can't do that automatically. To do that, you need\n"
"  to track when the login prompt is received and send the username and\n"
"  password accordingly.\n"
"\n"
"PERSISTENT CONNECTIONS\n"
"\n"
"  Specifying multiple files on a single command line will make curl transfer\n"
, stdout);