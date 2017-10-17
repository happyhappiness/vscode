fputs(
"              2)  On  windows, if there is no _curlrc file in the home dir, it\n"
"              checks for one in the same dir the executable curl is placed. On\n"
"              unix-like  systems,  it will simply try to load .curlrc from the\n"
"              determined home dir.\n"
"\n"
"              # --- Example file ---\n"
"              # this is a comment\n"
"              url = \"curl.haxx.se\"\n"
"              output = \"curlhere.html\"\n"
"              user-agent = \"superagent/1.0\"\n"
"\n"
, stdout);