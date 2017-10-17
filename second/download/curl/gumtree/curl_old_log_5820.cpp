fputs(
"       --hostpubmd5 <md5>\n"
"              Pass  a  string  containing  32  hexadecimal  digits. The string\n"
"              should be the 128 bit MD5 checksum of the remote  host's  public\n"
"              key,  curl  will  refuse the connection with the host unless the\n"
"              md5sums match. This option is only for SCP and  SFTP  transfers.\n"
"              (Added in 7.17.1)\n"
"\n"
"       --ignore-content-length\n"
"              (HTTP)  Ignore  the  Content-Length header. This is particularly\n"
, stdout);