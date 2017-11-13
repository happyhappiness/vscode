fputs(
"              redirects to follow by using the --max-redirs option.\n"
"\n"
"              When  curl follows a redirect and the request is not a plain GET\n"
"              (for example POST or PUT), it will do the following request with\n"
"              a GET if the HTTP response was 301, 302, or 303. If the response\n"
"              code was any other 3xx code, curl  will  re-send  the  following\n"
"              request using the same unmodified method.\n"
"\n"
, stdout);