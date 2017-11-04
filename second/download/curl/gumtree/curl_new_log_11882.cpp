fputs(
"              it  uses getpwuid() on Unix-like systems (which returns the home\n"
"              dir given the current user in your system). On Windows, it  then\n"
"              checks for the APPDATA variable, or as a last resort the '%USER-\n"
"              PROFILE%\\Application Data'.\n"
"\n"
"              2) On windows, if there is no _curlrc file in the home  dir,  it\n"
"              checks for one in the same dir the curl executable is placed. On\n"
, stdout);