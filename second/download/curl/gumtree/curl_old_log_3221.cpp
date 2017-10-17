fputs(
"       30     FTP PORT failed. The PORT command failed. Not  all  FTP  servers\n"
"              support  the  PORT  command,  try  doing  a  transfer using PASV\n"
"              instead!\n"
"\n"
"       31     FTP couldn’t use REST. The REST command failed. This command  is\n"
"              used for resumed FTP transfers.\n"
"\n"
"       32     FTP  couldn’t  use SIZE. The SIZE command failed. The command is\n"
"              an extension to the original FTP spec RFC 959.\n"
"\n"
, stdout);