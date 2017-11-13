fputs(
"              (HTTP/FTP/SFTP/FILE) Retrieve a byte range (i.e a partial  docu-\n"
"              ment)  from  a  HTTP/1.1,  FTP  or  SFTP server or a local FILE.\n"
"              Ranges can be specified in a number of ways.\n"
"\n"
"              0-499     specifies the first 500 bytes\n"
"\n"
"              500-999   specifies the second 500 bytes\n"
"\n"
"              -500      specifies the last 500 bytes\n"
"\n"
"              9500-     specifies the bytes from offset 9500 and forward\n"
"\n"
, stdout);