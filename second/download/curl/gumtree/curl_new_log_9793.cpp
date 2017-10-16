fputs(
"       Provide  the IPv6 zone index in the URL with an escaped percentage sign\n"
"       and the interface name. Like in\n"
"\n"
"         http://[fe80::3%25eth0]/\n"
"\n"
"       If you specify URL without protocol:// prefix,  curl  will  attempt  to\n"
"       guess  what  protocol  you might want. It will then default to HTTP but\n"
"       try other protocols based on often-used host name prefixes.  For  exam-\n"
"       ple,  for  host names starting with \"ftp.\" curl will assume you want to\n"
"       speak FTP.\n"
"\n"
, stdout);