fputs(
"              request, it does not alter the way curl behaves. So for  example\n"
"              if  you  want  to make a proper HEAD request, using -X HEAD will\n"
"              not suffice. You need to use the -I, --head option.\n"
"\n"
"              The method string you set with -X will be used for all requests,\n"
"              which if you for example use -L, --location may cause unintended\n"
"              side-effects when curl doesn't change request  method  according\n"
, stdout);