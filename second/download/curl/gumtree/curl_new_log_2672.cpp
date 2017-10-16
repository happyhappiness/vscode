fputs(
"              field from a file.\n"
"\n"
"              Example, to  send  your  password  file  to  the  server,  where\n"
"              ’password’  is  the  name of the form-field to which /etc/passwd\n"
"              will be the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
"              To read the file’s content from stdin instead of a file,  use  -\n"
"              where  the  file name should’ve been. This goes for both @ and <\n"
"              constructs.\n"
"\n"
, stdout);