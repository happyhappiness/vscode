fputs(
"       curl  normally  displays a progress meter during operations, indicating\n"
"       amount of transferred data, transfer speeds  and  estimated  time  left\n"
"       etc.\n"
"\n"
"       However,  since  curl  displays data to the terminal by default, if you\n"
"       invoke curl to do an operation and it is about to  write  data  to  the\n"
"       terminal,  it disables the progress meter as otherwise it would mess up\n"
"       the output mixing progress meter and response data.\n"
"\n"
, stdout);