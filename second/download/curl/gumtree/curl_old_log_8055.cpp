fputs(
"              Disabling EPRT only changes the active behavior. If you want  to\n"
"              switch  to  passive  mode  you need to not use -P, --ftp-port or\n"
"              force it with --ftp-pasv.\n"
"\n"
"       --disable-epsv\n"
"              (FTP) Tell curl to disable the use  of  the  EPSV  command  when\n"
"              doing  passive  FTP  transfers.  Curl will normally always first\n"
"              attempt to use EPSV before PASV, but with this option,  it  will\n"
"              not try using EPSV.\n"
"\n"
, stdout);