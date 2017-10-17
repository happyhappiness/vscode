fputs(
"              does  not support reading the file from a named pipe or similar,\n"
"              as it needs the full size before the transfer starts.\n"
"\n"
"              You can also  tell  curl  what  Content-Type  to  use  by  using\n"
"              'type=', in a manner similar to:\n"
"\n"
"              curl -F \"web=@index.html;type=text/html\" example.com\n"
"\n"
"              or\n"
"\n"
"              curl -F \"name=daniel;type=text/foo\" example.com\n"
"\n"
, stdout);