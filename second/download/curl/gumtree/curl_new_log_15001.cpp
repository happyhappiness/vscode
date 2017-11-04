fputs(
"  An HTTP request has the option to include information about the browser\n"
"  that generated the request. Curl allows it to be specified on the command\n"
"  line. It is especially useful to fool or trick stupid servers or CGI\n"
"  scripts that only accept certain browsers.\n"
"\n"
"  Example:\n"
"\n"
"  curl -A 'Mozilla/3.0 (Win95; I)' http://www.nationsbank.com/\n"
"\n"
"  Other common strings:\n"
"    'Mozilla/3.0 (Win95; I)'     Netscape Version 3 for Windows 95\n"
, stdout);