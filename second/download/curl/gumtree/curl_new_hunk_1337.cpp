"        curl http://name:passwd@machine.domain/full/path/to/file\n"
"\n"
"   or specify user and password separately like in\n"
"\n"
"        curl -u name:passwd http://machine.domain/full/path/to/file\n"
"\n"
);
 puts(
"   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
"   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
"   during such circumstances.\n"
"\n"
" HTTPS\n"
"\n"
