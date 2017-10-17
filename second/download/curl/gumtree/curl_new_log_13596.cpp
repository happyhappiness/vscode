fputs(
"    curl --metalink http://www.example.com/example.metalink\n"
"\n"
"  To use a Metalink file in the local file system, use FILE protocol (file://):\n"
"\n"
"    curl --metalink file://example.metalink\n"
"\n"
"  Please note that if FILE protocol is disabled, there is no way to use a local\n"
"  Metalink file at the time of this writing. Also note that if --metalink and\n"
"  --include are used together, --include will be ignored. This is because including\n"
, stdout);