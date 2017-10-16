fputs(
"   standards while the recommended \"explicit\" way is done by using FTP:// and\n"
"   the --ftp-ssl option.\n"
"\n"
" SFTP / SCP\n"
"\n"
"   This is similar to FTP, but you can use the --key option to specify a\n"
"   private key to use instead of a password. Note that the private key may\n"
"   itself be protected by a password that is unrelated to the login password\n"
"   of the remote system; this password is specified using the --pass option.\n"
"   Typically, curl will automatically extract the public key from the private\n"
, stdout);