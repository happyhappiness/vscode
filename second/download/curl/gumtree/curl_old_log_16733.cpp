puts(
"          If  this  option  is  used twice, the second will again\n"
"          switch on buffering.\n"
"\n"
"     -o/--output <file>\n"
"          Write output to <file> instead of stdout.  If  you  are\n"
"          using {} or [] to fetch multiple documents, you can use\n"
"          '#' followed by a number in the <file> specifier.  That\n"
"          variable  will  be replaced with the current string for\n"
"          the URL being fetched. Like in:\n"
"\n"
"            curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
"\n"
);