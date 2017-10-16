 "              doing  passive  FTP  transfers.  Curl will normally always first\n"
 "              attempt to use EPSV before PASV, but with this option,  it  will\n"
 "              not try using EPSV.\n"
 "\n"
 , stdout);
  fputs(
-"              --epsv can be used to explicitly enable EPRT again and --no-epsv\n"
+"              --epsv can be used to explicitly enable EPSV again and --no-epsv\n"
 "              is an alias for --disable-epsv.\n"
 "\n"
 "              Disabling EPSV only changes the passive behavior. If you want to\n"
 "              switch to active mode you need to use -P, --ftp-port.\n"
 "\n"
 "       -e, --referer <URL>\n"
