fputs(
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
, stdout);