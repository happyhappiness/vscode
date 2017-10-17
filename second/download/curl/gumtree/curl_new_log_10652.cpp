fputs(
"              -  Deny  this  protocol,  removing it from the list of protocols\n"
"                 already permitted.\n"
"\n"
"              =  Permit only this protocol (ignoring the list already  permit-\n"
"                 ted),  though  subject  to  later  modification by subsequent\n"
"                 entries in the comma separated list.\n"
"\n"
"              For example:\n"
"\n"
"              --proto -ftps  uses the default protocols, but disables ftps\n"
"\n"
"              --proto -all,https,+http\n"
, stdout);