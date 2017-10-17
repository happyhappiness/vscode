fputs(
"              makes a file get attached in the post as a  file  upload,  while\n"
"              the < makes a text field and just get the contents for that text\n"
"              field from a file.\n"
"\n"
"              Example, to send your password file to the server, where  'pass-\n"
"              word' is the name of the form-field to which /etc/passwd will be\n"
"              the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
, stdout);