fputs(
"              FTP(S)  server. The method argument should be one of the follow-\n"
"              ing alternatives:\n"
"\n"
"              multicwd\n"
"                     curl does a single CWD operation for each  path  part  in\n"
"                     the  given URL. For deep hierarchies this means very many\n"
"                     commands. This is how RFC 1738 says it  should  be  done.\n"
"                     This is the default but the slowest behavior.\n"
"\n"
, stdout);