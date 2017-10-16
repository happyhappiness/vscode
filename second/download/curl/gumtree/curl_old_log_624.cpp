fputs(
"              Example,  to send your password file to the server,\n"
"              where 'password' is the name of the  form-field  to\n"
"              which /etc/passwd will be the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
"              To  read  the file's content from stdin insted of a\n"
"              file, use - where the  file  name  should've  been.\n"
"              This goes for both @ and < constructs.\n"
"\n"
, stdout);