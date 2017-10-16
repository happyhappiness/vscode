"              uploading from stdin, the upload operation will fail.\n"
"\n"
"              If this option is used several times, the following  occurrences\n"
"              make no difference.\n"
"\n"
"       -b/--cookie <name=data>\n"
"              (HTTP)  Pass the data to the HTTP server as a cookie. It is sup‐\n"
, stdout);
 fputs(
"              posedly the data previously received from the server in a  \"Set-\n"
"              Cookie:\"  line.  The data should be in the format \"NAME1=VALUE1;\n"
"              NAME2=VALUE2\".\n"
"\n"
"              If no ’=’ letter is used in the line, it is treated as  a  file‐\n"
"              name  to  use to read previously stored cookie lines from, which\n"
"              should be used in this session if they match. Using this  method\n"
, stdout);
 fputs(
"              also  activates  the \"cookie parser\" which will make curl record\n"
"              incoming cookies too, which may be handy if you’re using this in\n"
"              combination  with  the  -L/--location option. The file format of\n"
"              the file to read cookies from should be plain  HTTP  headers  or\n"
"              the Netscape/Mozilla cookie file format.\n"
"\n"
"              NOTE  that  the  file specified with -b/--cookie is only used as\n"
, stdout);
 fputs(
"              input. No cookies will be stored in the file. To store  cookies,\n"
"              use  the  -c/--cookie-jar option or you could even save the HTTP\n"
"              headers to a file using -D/--dump-header!\n"
"\n"
"              If this option is set more than once, the last one will  be  the\n"
"              one that’s used.\n"
"\n"
"       -B/--use-ascii\n"
"              Enable  ASCII transfer when using FTP or LDAP. For FTP, this can\n"
, stdout);
 fputs(
"              also be enforced by using an URL that ends with \";type=A\".  This\n"
