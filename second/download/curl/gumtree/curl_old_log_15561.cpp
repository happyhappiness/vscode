fputs(
"  Curl supports .netrc files if told to (using the -n/--netrc and\n"
"  --netrc-optional options). This is not restricted to just FTP,\n"
"  so curl can use it for all protocols where authentication is used.\n"
"\n"
"  A very simple .netrc file could look something like:\n"
"\n"
"        machine curl.haxx.se login iamdaniel password mysecret\n"
"\n"
"CUSTOM OUTPUT\n"
"\n"
"  To better allow script programmers to get to know about the progress of\n"
"  curl, the -w/--write-out option was introduced. Using this, you can specify\n"
, stdout);