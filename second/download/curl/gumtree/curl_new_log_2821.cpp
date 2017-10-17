fputs(
"              server.  Quote  commands  are sent BEFORE the transfer is taking\n"
"              place (just after the initial PWD command in an FTP transfer, to\n"
"              be exact). To make commands take place after a successful trans‐\n"
"              fer, prefix them with a dash ’-’.  To  make  commands  get  sent\n"
"              after  libcurl  has  changed  working directory, just before the\n"
"              transfer command(s), prefix the command with ’+’ (this  is  only\n"
, stdout);