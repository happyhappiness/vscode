"  There's no use for a password on the -u switch, but a blank one will make\n"
"  curl ask for one and you already entered the real password to kauth.\n"
"\n"
"TELNET\n"
"\n"
"  The curl telnet support is basic and very easy to use. Curl passes all data\n"
"  passed to it on stdin to the remote server. Connect to a remote telnet\n"
"  server using a command line similar to:\n"
"\n"
"        curl telnet://remote.server.com\n"
"\n"
"  And enter the data to pass to the server on stdin. The result will be sent\n"
"  to stdout or to the file you specify with -o.\n"
"\n"
"  You might want the -N/--no-buffer option to switch off the buffered output\n"
"  for slow connections or similar.\n"
"\n"
"  NOTE: the telnet protocol does not specify any way to login with a specified\n"
"  user and password so curl can't do that automatically. To do that, you need\n"
"  to track when the login prompt is received and send the username and\n"
"  password accordingly.\n"
"\n"
"MAILING LIST\n"
"\n"
"  We have an open mailing list to discuss curl, its development and things\n"
"  relevant to this.\n"
"\n"
"  To subscribe, mail curl-request@contactor.se with \"subscribe <fill in your\n"
"  email address>\" in the body.\n"
"\n"
"  To post to the list, mail curl@contactor.se.\n"
"\n"
"  To unsubcribe, mail curl-request@contactor.se with \"unsubscribe <your\n"
"  subscribed email address>\" in the body.\n"
"\n"
 ) ;
}
