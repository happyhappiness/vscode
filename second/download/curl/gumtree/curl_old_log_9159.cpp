fputs(
"  look like:\n"
"\n"
"    sftp://[fe80::1234%251]/\n"
"\n"
"  IPv6 addresses provided other than in URLs (e.g. to the --proxy, --interface\n"
"  or --ftp-port options) should not be URL encoded.\n"
"\n"
"METALINK\n"
"\n"
"  Curl supports Metalink (both version 3 and 4 (RFC 5854) are supported), a way\n"
"  to list multiple URIs and hashes for a file. Curl will make use of the mirrors\n"
"  listed within for failover if there are errors (such as the file or server not\n"
, stdout);