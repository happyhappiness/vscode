fputs(
"       it disables the progress meter as otherwise it would mess up the output\n"
"       mixing progress meter and response data.\n"
"\n"
"       If you want a progress meter for HTTP POST or PUT requests, you need to\n"
"       redirect the response output to a file, using shell  redirect  (>),  -o\n"
"       [file] or similar.\n"
"\n"
"       It  is not the same case for FTP upload as that operation does not spit\n"
"       out any response data to the terminal.\n"
"\n"
, stdout);