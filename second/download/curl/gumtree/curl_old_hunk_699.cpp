, stdout);
 fputs(
"              server. Quote commands are sent BEFORE the transfer takes  place\n"
"              (just  after  the  initial PWD command in an FTP transfer, to be\n"
"              exact). To make commands take place after a successful transfer,\n"
"              prefix  them  with  a  dash '-'.  To make commands be sent after\n"
"              libcurl has changed  the  working  directory,  just  before  the\n"
"              transfer command(s), prefix the command with a '+' (this is only\n"
, stdout);
 fputs(
"              supported for FTP). You may specify any number of  commands.  If\n"
"              the  server  returns failure for one of the commands, the entire\n"
"              operation will be aborted. You must send  syntactically  correct\n"
"              FTP  commands  as  RFC 959 defines to FTP servers, or one of the\n"
"              commands listed below to SFTP servers.  This option can be  used\n"
"              multiple  times.  When speaking to a FTP server, prefix the com-\n"
, stdout);
 fputs(
"              mand with an asterisk (*) to make libcurl continue even  if  the\n"
"              command fails as by default curl will stop at first failure.\n"
"\n"
"              SFTP  is  a  binary protocol. Unlike for FTP, libcurl interprets\n"
"              SFTP quote commands itself before sending them  to  the  server.\n"
"              File  names may be quoted shell-style to embed spaces or special\n"
"              characters.  Following is the list of all supported  SFTP  quote\n"
"              commands:\n"
"\n"
, stdout);
 fputs(
"              chgrp group file\n"
"                     The  chgrp command sets the group ID of the file named by\n"
"                     the file operand to the group ID specified by  the  group\n"
