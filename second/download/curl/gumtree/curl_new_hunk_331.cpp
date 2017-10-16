"       separate curl invokes.\n"
"\n"
"PROGRESS METER\n"
, stdout);
 fputs(
"       curl  normally  displays a progress meter during operations, indicating\n"
"       the amount of transferred data,  transfer  speeds  and  estimated  time\n"
"       left, etc.\n"
"\n"
"       However,  since  curl displays this data to the terminal by default, if\n"
"       you invoke curl to do an operation and it is about to write data to the\n"
"       terminal,  it disables the progress meter as otherwise it would mess up\n"
"       the output mixing progress meter and response data.\n"
"\n"
, stdout);
 fputs(
"       If you want a progress meter for HTTP POST or PUT requests, you need to\n"
"       redirect  the  response  output to a file, using shell redirect (>), -o\n"
"       [file] or similar.\n"
"\n"
"       It is not the same case for FTP upload as that operation does not  spit\n"
"       out any response data to the terminal.\n"
"\n"
"       If you prefer a progress \"bar\" instead of the regular meter, -# is your\n"
"       friend.\n"
"OPTIONS\n"
"       In general, all boolean options are enabled with --option and yet again\n"
, stdout);
