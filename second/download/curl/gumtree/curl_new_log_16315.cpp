fputs(
"              You  can  add  custom  headers to the field by setting headers=,\n"
"              like\n"
"\n"
"                curl -F \"submit=OK;headers=\\\"X-submit-type: OK\\\"\" example.com\n"
"\n"
"              or\n"
"\n"
"                curl -F \"submit=OK;headers=@headerfile\" example.com\n"
"\n"
"              The headers= keyword may appear more that once and  above  notes\n"
"              about  quoting  apply.  When headers are read from a file, Empty\n"
, stdout);