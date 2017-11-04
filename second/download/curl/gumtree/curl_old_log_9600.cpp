fputs(
"  included in recent versions of OpenSSL, and for older versions Dr Stephen\n"
"  N. Henson has written a patch for SSLeay that adds this functionality. You\n"
"  can get his patch (that requires an SSLeay installation) from his site at:\n"
"  http://www.drh-consultancy.demon.co.uk/\n"
"\n"
"  Example on how to automatically retrieve a document using a certificate with\n"
"  a personal password:\n"
"\n"
"        curl -E /path/to/cert.pem:password https://secure.site.com/\n"
"\n"
, stdout);