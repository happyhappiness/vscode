, stdout);
 fputs(
"              server. Quote commands are sent BEFORE the transfer takes  place\n"
"              (just  after  the  initial PWD command in an FTP transfer, to be\n"
"              exact). To make commands take place after a successful transfer,\n"
"              prefix  them  with  a  dash '-'.  To make commands be sent after\n"
"              curl has changed the working directory, just before the transfer\n"
"              command(s),  prefix  the  command  with a '+' (this is only sup-\n"
, stdout);
 fputs(
"              ported for FTP). You may specify any number of commands. If  the\n"
"              server returns failure for one of the commands, the entire oper-\n"
"              ation will be aborted. You must send syntactically  correct  FTP\n"
"              commands  as  RFC 959 defines to FTP servers, or one of the com-\n"
"              mands listed below to SFTP servers.  This  option  can  be  used\n"
"              multiple  times. When speaking to an FTP server, prefix the com-\n"
, stdout);
 fputs(
"              mand with an asterisk (*) to make curl continue even if the com-\n"
"              mand fails as by default curl will stop at first failure.\n"
"\n"
"              SFTP  is a binary protocol. Unlike for FTP, curl interprets SFTP\n"
"              quote commands itself before sending them to the  server.   File\n"
"              names may be quoted shell-style to embed spaces or special char-\n"
"              acters.  Following is the list of all supported SFTP quote  com-\n"
"              mands:\n"
"\n"
, stdout);
 fputs(
"              chgrp group file\n"
"                     The  chgrp command sets the group ID of the file named by\n"
"                     the file operand to the group ID specified by  the  group\n"
