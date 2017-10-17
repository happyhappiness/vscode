fputs(
"              Write output to <file> instead of  stdout.  If  you\n"
"              are using {} or [] to fetch multiple documents, you\n"
"              can use '#' followed by  a  number  in  the  <file>\n"
"              specifier.  That variable will be replaced with the\n"
"              current string for the URL being fetched. Like in:\n"
"\n"
"                curl http://{one,two}.site.com -o \"file_#1.txt\"\n"
"\n"
"              or use several variables like:\n"
"\n"
, stdout);