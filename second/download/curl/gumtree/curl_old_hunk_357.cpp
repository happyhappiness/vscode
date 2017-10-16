"              posedly  the data previously received from the server in a \"Set-\n"
"              Cookie:\" line.  The data should be in the format  \"NAME1=VALUE1;\n"
"              NAME2=VALUE2\".\n"
"\n"
, stdout);
 fputs(
"              If  no  '=' letter is used in the line, it is treated as a file-\n"
"              name to use to read previously stored cookie lines  from,  which\n"
"              should  be used in this session if they match. Using this method\n"
"              also activates the \"cookie parser\" which will make  curl  record\n"
"              incoming cookies too, which may be handy if you're using this in\n"
"              combination with the -L/--location option. The  file  format  of\n"
, stdout);
