fputs(
"   Note that using FTPS:// as prefix is the \"implicit\" way as described in the\n"
"   standards while the recommended \"explicit\" way is done by using FTP:// and\n"
"   the --ftp-ssl option.\n"
"\n"
" SFTP / SCP\n"
"\n"
"   This is similar to FTP, but you can specify a private key to use instead of\n"
"   a password. Note that the private key may itself be protected by a password\n"
"   that is unrelated to the login password of the remote system.  If you\n"
"   provide a private key file you must also provide a public key file.\n"
, stdout);