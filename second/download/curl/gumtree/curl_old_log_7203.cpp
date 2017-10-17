fputs(
"       30     FTP PORT failed. The PORT command failed. Not  all  FTP  servers\n"
"              support  the  PORT  command,  try  doing  a  transfer using PASV\n"
"              instead!\n"
"\n"
"       31     FTP couldn't use REST. The REST command failed. This command  is\n"
"              used for resumed FTP transfers.\n"
"\n"
"       33     HTTP range error. The range \"command\" didn't work.\n"
"\n"
"       34     HTTP post error. Internal post-request generation error.\n"
"\n"
, stdout);