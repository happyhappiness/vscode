fputs(
"  user and password so curl can't do that automatically. To do that, you need\n"
"  to track when the login prompt is received and send the username and\n"
"  password accordingly.\n"
"\n"
"PERSISTENT CONNECTIONS\n"
"\n"
"  Specifying multiple files on a single command line will make curl transfer\n"
"  all of them, one after the other in the specified order.\n"
"\n"
"  libcurl will attempt to use persistent connections for the transfers so that\n"
"  the second transfer to the same host can use the same connection that was\n"
, stdout);