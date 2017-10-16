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