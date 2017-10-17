fputs(
"                        specifies 300 bytes from offset 500(H)\n"
"\n"
"              100-199,500-599\n"
"                        specifies two separate 100-byte ranges(*)(H)\n"
"\n"
"       (*) = NOTE that this will cause the server to reply  with  a  multipart\n"
"       response!\n"
"\n"
"       Only  digit characters (0-9) are valid in the 'start' and 'stop' fields\n"
"       of the 'start-stop' range syntax. If a non-digit character is given  in\n"
"       the  range, the server's response will be unspecified, depending on the\n"
, stdout);