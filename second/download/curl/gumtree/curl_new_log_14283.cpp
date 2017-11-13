fputs(
"              default config file is checked for in the  following  places  in\n"
"              this order:\n"
"\n"
"              1)  curl  tries  to find the \"home dir\": It first checks for the\n"
"              CURL_HOME and then the HOME environment variables. Failing that,\n"
"              it  uses getpwuid() on Unix-like systems (which returns the home\n"
"              dir given the current user in your system). On Windows, it  then\n"
, stdout);