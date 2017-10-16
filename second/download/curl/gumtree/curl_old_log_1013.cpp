fputs(
"              which /etc/passwd will be the input:\n"
"\n"
"              curl -F password=@/etc/passwd www.mypasswords.com\n"
"\n"
"              To  read  the file's content from stdin insted of a\n"
"              file, use - where the  file  name  should've  been.\n"
"              This goes for both @ and < constructs.\n"
"\n"
"              You can also tell curl what Content-Type to use for\n"
"              the file upload part, by using 'type=', in a manner\n"
"              similar to:\n"
"\n"
, stdout);