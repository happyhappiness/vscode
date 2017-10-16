fputs(
" client's perspective, with special commands to select the remote FTP server.\n"
" curl supports the -u, -Q and --ftp-account options that can be used to\n"
" set up transfers through many FTP proxies. For example, a file can be\n"
" uploaded to a remote FTP server using a Blue Coat FTP proxy with the\n"
" options:\n"
"\n"
"   curl -u \"Remote-FTP-Username@remote.ftp.server Proxy-Username:Remote-Pass\" \\\n"
"    --ftp-account Proxy-Password --upload-file local-file \\\n"
"    ftp://my-ftp.proxy.server:21/remote/upload/path/\n"
"\n"
, stdout);