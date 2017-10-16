"                     than 2GB.\n"
"\n"
, stdout);
 fputs(
"              IDN    This curl supports IDN - international domain names.\n"
"\n"
"              SSPI   SSPI  is  supported. If you use NTLM and set a blank user\n"
"                     name, curl will authenticate with your current  user  and\n"
"                     password.\n"
"\n"
"              TLS-SRP\n"
"                     SRP  (Secure Remote Password) authentication is supported\n"
"                     for TLS.\n"
"              Metalink\n"
"                     This curl supports Metalink (both version 3  and  4  (RFC\n"
, stdout);
 fputs(
"                     5854)),  which  describes  mirrors and hashes.  curl will\n"
"                     use mirrors for failover if there are errors (such as the\n"
"                     file or server not being available).\n"
"\n"
"FILES\n"
"       ~/.curlrc\n"
"              Default config file, see -K, --config for details.\n"
