fputs(
"    curl --metalink file://example.metalink\n"
"\n"
"  Please note that if FILE protocol is disabled, there is no way to use a local\n"
"  Metalink file at the time of this writing. Also note that if --metalink and\n"
"  --include are used together, --include will be ignored. This is because including\n"
"  headers in the response will break Metalink parser and if the headers are included\n"
"  in the file described in Metalink file, hash check will fail.\n"
"\n"
"MAILING LISTS\n"
"\n"
, stdout);