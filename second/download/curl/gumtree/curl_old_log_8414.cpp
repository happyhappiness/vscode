fputs(
"              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
"\n"
"       --tcp-nodelay\n"
"              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
"              page for details about this option. (Added in 7.11.2)\n"
"\n"
"       --tftp-blksize <value>\n"
"              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
"              size that curl will try to use when transferring data to or from\n"
"              a TFTP server. By default 512 bytes will be used.\n"
"\n"
, stdout);