fputs(
"              1)  curl  tries  to find the \"home dir\": It first checks for the\n"
"              CURL_HOME and then the HOME environment variables. Failing that,\n"
"              it  uses getpwuid() on unix-like systems (which returns the home\n"
"              dir given the current user in your system). On Windows, it  then\n"
"              checks for the APPDATA variable, or as a last resort the '%USER-\n"
"              PROFILE%0lication Data'.\n"
"\n"
, stdout);