fputs(
"  Or prevent curl from uploading data faster than 1 megabyte per second:\n"
"\n"
"        curl -T upload --limit-rate 1M ftp://uploadshereplease.com\n"
"\n"
"  When using the --limit-rate option, the transfer rate is regulated on a\n"
"  per-second basis, which will cause the total transfer speed to become lower\n"
"  than the given number. Sometimes of course substantially lower, if your\n"
"  transfer stalls during periods.\n"
"\n"
"CONFIG FILE\n"
"\n"
"  Curl automatically tries to read the .curlrc file (or _curlrc file on win32\n"
, stdout);