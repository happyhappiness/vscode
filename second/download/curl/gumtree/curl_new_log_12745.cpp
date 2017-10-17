fputs(
"       -e, --referer <URL>\n"
"              (HTTP) Sends the \"Referrer Page\" information to the HTTP server.\n"
"              This can also be set with the -H, --header flag of course.  When\n"
"              used with -L, --location you can append \";auto\" to the --referer\n"
"              URL to make curl automatically set the previous URL when it fol-\n"
"              lows a Location: header. The \";auto\" string can be  used  alone,\n"
"              even if you don't set an initial --referer.\n"
"\n"
, stdout);