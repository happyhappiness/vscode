fputs(
"              # --- Example file ---\n"
"              # this is a comment\n"
"              url = \"curl.haxx.se\"\n"
"              output = \"curlhere.html\"\n"
"              user-agent = \"superagent/1.0\"\n"
"\n"
"              # and fetch another URL too\n"
"              url = \"curl.haxx.se/docs/manpage.html\"\n"
"              -O\n"
"              referer = \"http://nowhereatall.com/\"\n"
"              # --- End of example file ---\n"
"\n"
"              This  option  can be used multiple times to load multiple config\n"
"              files.\n"
"\n"
, stdout);