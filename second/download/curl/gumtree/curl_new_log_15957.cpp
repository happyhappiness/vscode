fputs(
"              file. Using @- will make curl read the header file from stdin.\n"
"\n"
"              See also the -A, --user-agent and -e, --referer options.\n"
"\n"
"              Starting in 7.37.0, you need --proxy-header to send custom head-\n"
"              ers intended for a proxy.\n"
"\n"
"              Example:\n"
"\n"
"               curl -H \"X-First-Name: Joe\" http://example.com/\n"
"\n"
"              WARNING: headers set  with  this  option  will  be  set  in  all\n"
, stdout);