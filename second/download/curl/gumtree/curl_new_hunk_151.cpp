"\n"
"              SSPI   SSPI is supported. If you use NTLM and set a  blank  user\n"
"                     name,  curl  will authenticate with your current user and\n"
"                     password.\n"
"\n"
"       -w/--write-out <format>\n"
"              Defines what to display on stdout after a completed and success-\n"
"              ful  operation.  The  format  is a string that may contain plain\n"
, stdout);
 fputs(
"              text mixed with any number of variables. The string can be spec-\n"
"              ified  as \"string\", to get read from a particular file you spec-\n"
"              ify it \"@filename\" and to tell curl  to  read  the  format  from\n"
"              stdin you write \"@-\".\n"
"\n"
"              The  variables  present in the output format will be substituted\n"
"              by the value or text that curl thinks fit, as  described  below.\n"
, stdout);
 fputs(
"              All  variables are specified like %{variable_name} and to output\n"
