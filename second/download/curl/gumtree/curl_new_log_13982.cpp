fputs(
"                curl -o aa example.com -o bb example.net\n"
"\n"
"              and the order of the -o options and  the  URLs  doesn't  matter,\n"
"              just  that  the  first -o is for the first URL and so on, so the\n"
"              above command line can also be written as\n"
"\n"
"                curl example.com example.net -o aa -o bb\n"
"\n"
"              See also the --create-dirs option to create the  local  directo-\n"
"              ries  dynamically.  Specifying the output as '-' (a single dash)\n"
, stdout);