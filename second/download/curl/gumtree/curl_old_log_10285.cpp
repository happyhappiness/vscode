fputs(
"              For example:\n"
"\n"
"              --proto -ftps  uses the default protocols, but disables ftps\n"
"\n"
"              --proto -all,https,+http\n"
"                             only enables http and https\n"
"\n"
"              --proto =http,https\n"
"                             also only enables http and https\n"
"\n"
"              Unknown  protocols  produce  a  warning.  This allows scripts to\n"
"              safely rely on being able to disable potentially dangerous  pro-\n"
, stdout);