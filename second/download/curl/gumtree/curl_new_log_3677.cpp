fputs(
"                     commands. This is how RFC1738 says  it  should  be  done.\n"
"                     This is the default but the slowest behavior.\n"
"\n"
"              nocwd  curl  does  no  CWD at all. curl will do SIZE, RETR, STOR\n"
"                     etc and give a full path to the server for all these com-\n"
"                     mands. This is the fastest behavior.\n"
"\n"
"              singlecwd\n"
"                     curl does one CWD with the full target directory and then\n"
, stdout);