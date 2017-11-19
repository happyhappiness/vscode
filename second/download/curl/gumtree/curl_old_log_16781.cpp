puts(
"   The HTTP URL doesn't support user and password in the URL string. Curl\n"
"   does support that anyway to provide a ftp-style interface and thus you can\n"
"   pick a file like:\n"
"\n"
"        curl http://name:passwd@machine.domain/full/path/to/file\n"
"\n"
"   or specify user and password separately like in\n"
"\n"
"        curl -u name:passwd http://machine.domain/full/path/to/file\n"
"\n"
"   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
);