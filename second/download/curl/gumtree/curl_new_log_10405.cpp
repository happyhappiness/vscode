fputs(
"              request, it does not alter the way curl behaves. So for  example\n"
"              if  you  want  to make a proper HEAD request, using -X HEAD will\n"
"              not suffice. You need to use the -I, --head option.\n"
"\n"
"              The the method string you set with  -X  will  be  used  for  all\n"
"              requests,  which if you for example use -L, --location may cause\n"
"              unintended side-effects when curl doesn't change request  method\n"
, stdout);