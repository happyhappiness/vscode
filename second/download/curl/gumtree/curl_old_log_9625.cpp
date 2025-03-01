fputs(
"  name for the second:\n"
"\n"
"    curl -O http://url.com/file.txt ftp://ftp.com/moo.exe -o moo.jpg\n"
"\n"
"  You can also upload multiple files in a similar fashion:\n"
"\n"
"    curl -T local1 ftp://ftp.com/moo.exe -T local2 ftp://ftp.com/moo2.txt\n"
"\n"
"IPv6\n"
"\n"
"  curl will connect to a server with IPv6 when a host lookup returns an IPv6\n"
"  address and fall back to IPv4 if the connection fails. The --ipv4 and --ipv6\n"
"  options can specify which address to use when both are available. IPv6\n"
, stdout);