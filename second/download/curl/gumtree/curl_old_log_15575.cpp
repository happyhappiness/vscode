fputs(
"              with the proper end-of-line marker, you should thus not add that\n"
"              as a part of the header content: do not add newlines or carriage\n"
"              returns, they will only mess things up for you.\n"
"\n"
"              See also the -A, --user-agent and -e, --referer options.\n"
"\n"
"              Starting in 7.37.0, you need --proxy-header to send custom head-\n"
"              ers intended for a proxy.\n"
"\n"
"              Example:\n"
"\n"
"               curl -H \"X-First-Name: Joe\" http://example.com/\n"
, stdout);