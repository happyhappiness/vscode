fputs(
"       -C/--continue-at <offset>\n"
"              Continue/Resume a previous file transfer at  the  given  offset.\n"
"              The  given  offset  is  the  exact  number of bytes that will be\n"
"              skipped counted from the beginning of the source file before  it\n"
"              is  transferred  to  the destination.  If used with uploads, the\n"
"              ftp server command SIZE will not be used by curl.\n"
"\n"
"              Use \"-C -\" to tell curl to automatically find out  where/how  to\n"
, stdout);