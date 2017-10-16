fputs(
"              When curl is invoked, it always (unless -q is used) checks for a\n"
"              default config file and uses it if  found.  The  default  config\n"
"              file is checked for in the following places in this order:\n"
"\n"
"              1)  curl  tries  to find the \"home dir\": It first checks for the\n"
"              CURL_HOME and then the HOME environment variables. Failing that,\n"
"              it  uses getpwuid() on UNIX-like systems (which returns the home\n"
, stdout);