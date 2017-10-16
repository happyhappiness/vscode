"\n"
"              SSPI   SSPI is supported. If you use NTLM and set a  blank  user\n"
"                     name,  curl  will authenticate with your current user and\n"
"                     password.\n"
"\n"
"       -w/--write-out <format>\n"
"              Defines what to display after a completed and successful  opera-\n"
"              tion.  The  format is a string that may contain plain text mixed\n"
, stdout);
 fputs(
"              with any number of variables. The string  can  be  specified  as\n"
"              \"string\",  to  get  read  from  a particular file you specify it\n"
"              \"@filename\" and to tell curl to read the format from  stdin  you\n"
"              write \"@-\".\n"
"\n"
"              The  variables  present in the output format will be substituted\n"
"              by the value or text that curl thinks fit, as  described  below.\n"
, stdout);
 fputs(
"              All  variables are specified like %{variable_name} and to output\n"
