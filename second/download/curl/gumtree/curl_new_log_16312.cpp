fputs(
"              the  name  of  the  form-field to which portrait.jpg will be the\n"
"              input:\n"
"\n"
"               curl -F profile=@portrait.jpg https://example.com/upload.cgi\n"
"\n"
"              To read content from stdin instead of a file, use - as the file-\n"
"              name.  This  goes  for both @ and < constructs. Unfortunately it\n"
"              does not support reading the file from a named pipe or  similar,\n"
"              as it needs the full size before the transfer starts.\n"
"\n"
, stdout);