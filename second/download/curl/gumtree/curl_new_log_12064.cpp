fputs(
"              0-0,-1    specifies the first and last byte only(*)(HTTP)\n"
"\n"
"              100-199,500-599\n"
"                        specifies two separate 100-byte ranges(*) (HTTP)\n"
"\n"
"              (*)  = NOTE that this will cause the server to reply with a mul-\n"
"              tipart response!\n"
"\n"
"              Only digit characters (0-9) are valid in the 'start' and  'stop'\n"
"              fields  of the 'start-stop' range syntax. If a non-digit charac-\n"
, stdout);