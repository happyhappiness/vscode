fputs(
"  and site local addresses including a scope identifier, such as fe80::1234%1,\n"
"  may also be used, but the scope portion must be numeric or match an existing\n"
"  network interface on Linux and the percent character must be URL escaped. The\n"
"  previous example in an SFTP URL might look like:\n"
"\n"
"    sftp://[fe80::1234%251]/\n"
"\n"
"  IPv6 addresses provided other than in URLs (e.g. to the --proxy, --interface\n"
"  or --ftp-port options) should not be URL encoded.\n"
"\n"
"METALINK\n"
"\n"
, stdout);