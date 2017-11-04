fputs(
"              (HTTP) Fail silently (no output at all) on server  errors.  This\n"
"              is  mostly done to better enable scripts etc to better deal with\n"
"              failed attempts. In normal cases when an HTTP  server  fails  to\n"
"              deliver  a  document,  it  returns  an  HTML document stating so\n"
"              (which often also describes why and more). This flag  will  pre-\n"
"              vent curl from outputting that and return error 22.\n"
"\n"
, stdout);