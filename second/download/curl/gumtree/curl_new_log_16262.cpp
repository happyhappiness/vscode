fputs(
"              When curl is invoked, it (unless -q, --disable is  used)  checks\n"
"              for a default config file and uses it if found. The default con-\n"
"              fig file is checked for in the following places in this order:\n"
"\n"
"              1) curl tries to find the \"home dir\": It first  checks  for  the\n"
"              CURL_HOME and then the HOME environment variables. Failing that,\n"
"              it uses getpwuid() on Unix-like systems (which returns the  home\n"
, stdout);