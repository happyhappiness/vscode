fputs(
"                curl http://{site,host}.host[1-5].com -o \"#1_#2\"\n"
"\n"
"              You  may use this option as many times as the number of URLs you\n"
"              have.\n"
"\n"
"              See also the --create-dirs option to create the  local  directo-\n"
"              ries  dynamically.  Specifying the output as '-' (a single dash)\n"
"              will force the output to be done to stdout.\n"
"\n"
"       -O/--remote-name\n"
"              Write output to a local file named like the remote file we  get.\n"
, stdout);