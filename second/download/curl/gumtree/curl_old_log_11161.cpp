fputs(
"  fool or trick stupid servers or CGI scripts that rely on that information\n"
"  being available or contain certain data.\n"
"\n"
"        curl -e www.coolsite.com http://www.showme.com/\n"
"\n"
"  NOTE: The Referer: [sic] field is defined in the HTTP spec to be a full URL.\n"
"\n"
"USER AGENT\n"
"\n"
"  An HTTP request has the option to include information about the browser\n"
"  that generated the request. Curl allows it to be specified on the command\n"
"  line. It is especially useful to fool or trick stupid servers or CGI\n"
, stdout);