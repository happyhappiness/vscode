fputs(
"              files.\n"
"\n"
"       --connect-timeout <seconds>\n"
"              Maximum  time  in  seconds  that  you allow curl's connection to\n"
"              take.  This only limits the connection phase, so  if  curl  con-\n"
"              nects  within the given period it will continue - if not it will\n"
"              exit.  Since version 7.32.0, this option accepts decimal values.\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"              See also -m, --max-time.\n"
"\n"
, stdout);