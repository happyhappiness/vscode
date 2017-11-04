fputs(
"       -n, --netrc\n"
"              Makes  curl  scan  the  .netrc  (_netrc  on Windows) file in the\n"
"              user's home directory for login name and password. This is typi-\n"
"              cally  used for FTP on Unix. If used with HTTP, curl will enable\n"
"              user authentication. See netrc(5) ftp(1) for details on the file\n"
"              format.  Curl  will  not  complain if that file doesn't have the\n"
"              right permissions (it should not be either world- or group-read-\n"
, stdout);