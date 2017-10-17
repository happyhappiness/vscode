fputs(
"              doing passive FTP transfers. Curl  will  normally  always  first\n"
"              attempt  to  use EPSV before PASV, but with this option, it will\n"
"              not try using EPSV.\n"
"\n"
"              Since curl 7.19.0, --epsv can be used to explicitly enable  EPRT\n"
"              again and --no-epsv is an alias for --disable-epsv.\n"
"\n"
"              Disabling EPSV only changes the passive behavior. If you want to\n"
"              switch to active mode you need to use -P/--ftp-port.\n"
"\n"
, stdout);