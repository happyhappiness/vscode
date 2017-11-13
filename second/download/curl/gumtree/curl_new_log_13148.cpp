fputs(
"       curl displays this data to the terminal by default, so  if  you  invoke\n"
"       curl  to do an operation and it is about to write data to the terminal,\n"
"       it disables the progress meter as otherwise it would mess up the output\n"
"       mixing progress meter and response data.\n"
"\n"
"       If you want a progress meter for HTTP POST or PUT requests, you need to\n"
"       redirect the response output to a file, using shell  redirect  (>),  -o\n"
"       [file] or similar.\n"
"\n"
, stdout);