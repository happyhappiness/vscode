 "  user and password so curl can't do that automatically. To do that, you need\n"
 "  to track when the login prompt is received and send the username and\n"
 "  password accordingly.\n"
 "\n"
 "PERSISTANT CONNECTIONS\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  Specifying multiple files on a single command line will make curl transfer\n"
 "  all of them, one after the other in the specified order.\n"
 "\n"
 "  libcurl will attempt to use persistant connections for the transfers so that\n"
 "  the second transfer to the same host can use the same connection that was\n"
 "  already initiated and was left open in the previous transfer. This greatly\n"
 "  decreases connection time for all but the first transfer and it makes a far\n"
 "  better use of the network.\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  Note that curl cannot use persistant connections for transfers that are used\n"
 "  in subsequence curl invokes. Try to stuff as many URLs as possible on the\n"
 "  same command line if they are using the same host, as that'll make the\n"
 "  transfers faster. If you use a http proxy for file transfers, practicly\n"
 "  all transfers will be persistant.\n"
 "\n"
 "  Persistant connections were introduced in curl 7.7.\n"
 "\n"
 "MAILING LISTS\n"
 "\n"
 "  For your convenience, we have several open mailing lists to discuss curl,\n"
-);
- puts(
+, stdout);
+ fputs(
 "  its development and things relevant to this. Get all info at\n"
 "  http://curl.haxx.se/mail/. The lists available are:\n"
 "\n"
 "  curl-users\n"
 "\n"
 "    Users of the command line tool. How to use it, what doesn't work, new\n"
