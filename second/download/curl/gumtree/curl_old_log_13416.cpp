fputs(
"              (for example POST or PUT), it will do the following request with\n"
"              a GET if the HTTP response was 301, 302, or 303. If the response\n"
"              code was any other 3xx code, curl  will  re-send  the  following\n"
"              request using the same unmodified method.\n"
"\n"
"              You  can  tell  curl to not change the non-GET request method to\n"
"              GET after a 30x response by  using  the  dedicated  options  for\n"
, stdout);