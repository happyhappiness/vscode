"              The  data  should  be  in the format \"NAME1=VALUE1;\n"
"              NAME2=VALUE2\".\n"
"\n"
"              If no '=' letter is used in the line, it is treated\n"
"              as  a  filename  to  use  to read previously stored\n"
"              cookie lines from, which should  be  used  in  this\n"
"              session if they match. Using this method also acti­\n"
, stdout);
 fputs(
"              vates the \"cookie  parser\"  which  will  make  curl\n"
"              record  incoming cookies too, which may be handy if\n"
"              you're  using  this   in   combination   with   the\n"
"              -L/--location  option.  The file format of the file\n"
