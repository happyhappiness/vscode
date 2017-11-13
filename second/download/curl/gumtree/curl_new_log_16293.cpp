fputs(
"              Disabling EPRT only changes the active behavior. If you want  to\n"
"              switch  to  passive  mode  you need to not use -P, --ftp-port or\n"
"              force it with --ftp-pasv.\n"
"\n"
"       --disable-epsv\n"
"              (FTP) (FTP) Tell curl to disable the use  of  the  EPSV  command\n"
"              when  doing  passive  FTP  transfers.  Curl will normally always\n"
"              first attempt to use EPSV before PASV, but with this option,  it\n"
"              will not try using EPSV.\n"
"\n"
, stdout);