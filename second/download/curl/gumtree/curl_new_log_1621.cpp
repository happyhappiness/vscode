fputs(
"              (FTP)  Send an arbitrary command to the remote FTP server. Quote\n"
"              commands are sent BEFORE the  transfer  is  taking  place  (just\n"
"              after  the  initial  PWD  command to be exact). To make commands\n"
"              take place after a successful transfer, prefix them with a  dash\n"
"              '-'. To make commands get sent after libcurl has changed working\n"
"              directory, just before the transfer command(s), prefix the  com-\n"
, stdout);