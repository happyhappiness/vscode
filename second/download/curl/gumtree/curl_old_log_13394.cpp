fputs(
"              For HTTP, Ignore the Content-Length header. This is particularly\n"
"              useful for servers running Apache 1.x, which will report  incor-\n"
"              rect Content-Length for files larger than 2 gigabytes.\n"
"\n"
"              For  FTP (since 7.46.0), skip the RETR command to figure out the\n"
"              size before downloading a file.\n"
"\n"
"       -i, --include\n"
"              (HTTP) Include the HTTP-header in the  output.  The  HTTP-header\n"
, stdout);