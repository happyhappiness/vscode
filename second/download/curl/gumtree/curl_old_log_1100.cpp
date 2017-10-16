fputs(
"              FTP servers support the PORT command, try  doing  a\n"
"              transfer using PASV instead!\n"
"\n"
"       31     FTP  couldn't  use  REST.  The REST command failed.\n"
"              This command is used for resumed FTP transfers.\n"
"\n"
"       32     FTP couldn't use SIZE. The SIZE command failed. The\n"
"              command  is  an  extension to the original FTP spec\n"
"              RFC 959.\n"
"\n"
"       33     HTTP range error. The range \"command\" didn't  work.\n"
, stdout);