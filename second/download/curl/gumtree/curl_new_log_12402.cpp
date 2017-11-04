fputs(
"       --disable-epsv\n"
"              (FTP)  Tell  curl  to  disable  the use of the EPSV command when\n"
"              doing passive FTP transfers. Curl  will  normally  always  first\n"
"              attempt  to  use EPSV before PASV, but with this option, it will\n"
"              not try using EPSV.\n"
"\n"
"              --epsv can be used to explicitly enable EPSV again and --no-epsv\n"
"              is an alias for --disable-epsv.\n"
"\n"
"              If  the  server is an IPv6 host, this option will have no effect\n"
, stdout);