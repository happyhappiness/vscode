fputs(
"       -Q/--quote <command>\n"
"              (FTP/SFTP)  Send  an arbitrary command to the remote FTP or SFTP\n"
"              server. Quote commands are sent BEFORE the transfer takes  place\n"
"              (just  after  the  initial PWD command in an FTP transfer, to be\n"
"              exact). To make commands take place after a successful transfer,\n"
"              prefix  them  with  a  dash '-'.  To make commands be sent after\n"
, stdout);