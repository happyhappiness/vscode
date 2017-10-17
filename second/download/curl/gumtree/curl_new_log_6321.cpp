fputs(
"              deliver a document, it  returns  an  HTML  document  stating  so\n"
"              (which  often  also describes why and more). This flag will pre-\n"
"              vent curl from outputting that and return error 22.\n"
"\n"
"              This method is not fail-safe and there are occasions where  non-\n"
"              successful  response  codes  will  slip through, especially when\n"
"              authentication is involved (response codes 401 and 407).\n"
"\n"
"       -F, --form <name=content>\n"
, stdout);