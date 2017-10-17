fputs(
"  being available). It will also verify the hash of the file after the download\n"
"  completes. The Metalink file itself is downloaded and processed in memory and\n"
"  not stored in the local file system.\n"
"\n"
"  Example to use a remote Metalink file:\n"
"\n"
"    curl --metalink http://www.example.com/example.metalink\n"
"\n"
"  To use a Metalink file in the local file system, use FILE protocol (file://):\n"
"\n"
"    curl --metalink file://example.metalink\n"
"\n"
, stdout);