fputs(
"       --disable-epsv\n"
"              (FTP)  (FTP)  Tell  curl  to disable the use of the EPSV command\n"
"              when doing passive FTP  transfers.  Curl  will  normally  always\n"
"              first  attempt to use EPSV before PASV, but with this option, it\n"
"              will not try using EPSV.\n"
"\n"
"              --epsv can be used to explicitly enable EPSV again and --no-epsv\n"
"              is an alias for --disable-epsv.\n"
"\n"
, stdout);