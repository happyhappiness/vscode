fputs(
"              Tells  curl to use the listed protocols on redirect. See --proto\n"
"              for how protocols are represented.\n"
"\n"
"              Example:\n"
"\n"
"              --proto-redir -all,http,https\n"
"                     Allow only HTTP and HTTPS on redirect.\n"
"\n"
"       By default curl will allow all protocols  on  redirect  except  several\n"
"       disabled  for security reasons: Since 7.19.4 FILE and SCP are disabled,\n"
"       and since 7.40.0 SMB and SMBS are also disabled. Specifying all or +all\n"
, stdout);