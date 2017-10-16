fputs(
"       you invoke curl to do an operation and it is about to write data to the\n"
"       terminal,  it disables the progress meter as otherwise it would mess up\n"
"       the output mixing progress meter and response data.\n"
"\n"
"       If you want a progress meter for HTTP POST or PUT requests, you need to\n"
"       redirect  the  response  output to a file, using shell redirect (>), -o\n"
"       [file] or similar.\n"
"\n"
"       It is not the same case for FTP upload as that operation does not  spit\n"
, stdout);