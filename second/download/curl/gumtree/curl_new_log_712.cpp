fputs(
"              upload, while the < makes a text field and just get\n"
"              the contents for that text field from a file.\n"
"\n"
"              Example, to send your password file to the  server,\n"
"              where  'password'  is the name of the form-field to\n"
"              which /etc/passwd will be the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
"              To read the file's content from stdin insted  of  a\n"
, stdout);