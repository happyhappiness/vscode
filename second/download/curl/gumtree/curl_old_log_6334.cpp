fputs(
"              Example,  to send your password file to the server, where 'pass-\n"
"              word' is the name of the form-field to which /etc/passwd will be\n"
"              the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
"              To read content from stdin instead of a file, use - as the file-\n"
"              name. This goes for both @ and < constructs.\n"
"\n"
"              You can also  tell  curl  what  Content-Type  to  use  by  using\n"
, stdout);