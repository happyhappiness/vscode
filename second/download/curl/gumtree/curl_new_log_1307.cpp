fputs(
"        curl -F \"docpicture=@dog.gif\" -F \"catpicture=@cat.gif\" \n"
"\n"
"REFERRER\n"
"\n"
"  A HTTP request has the option to include information about which address\n"
"  that referred to actual page.  Curl allows you to specify the\n"
"  referrer to be used on the command line. It is especially useful to\n"
"  fool or trick stupid servers or CGI scripts that rely on that information\n"
"  being available or contain certain data.\n"
"\n"
"        curl -e www.coolsite.com http://www.showme.com/\n"
"\n"
, stdout);