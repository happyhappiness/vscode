fputs(
"              mand line options.\n"
"\n"
"              This  option  only  changes  the  actual  word  used in the HTTP\n"
"              request, it does not alter the way curl behaves. So for  example\n"
"              if  you  want  to make a proper HEAD request, using -X HEAD will\n"
"              not suffice. You need to use the -I, --head option.\n"
"\n"
"              The method string you set with -X, --request will  be  used  for\n"
"              all  requests,  which  if you for example use -L, --location may\n"
, stdout);