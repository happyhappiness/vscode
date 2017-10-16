"KERBEROS FTP TRANSFER\n"
"\n"
"  Curl supports kerberos4 and kerberos5/GSSAPI for FTP transfers. You need\n"
, stdout);
 fputs(
"  the kerberos package installed and used at curl build time for it to be\n"
"  used.\n"
"\n"
"  First, get the krb-ticket the normal way, like with the kinit/kauth tool.\n"
"  Then use curl in way similar to:\n"
"\n"
"        curl --krb private ftp://krb4site.com -u username:fakepwd\n"
"\n"
