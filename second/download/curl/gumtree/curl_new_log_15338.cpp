fputs(
"\n"
"              --proto -all,https,+http\n"
"                             only enables http and https\n"
"\n"
"              --proto =http,https\n"
"                             also only enables http and https\n"
"\n"
"       Unknown protocols produce a warning. This allows scripts to safely rely\n"
"       on being able to disable potentially dangerous protocols, without rely-\n"
"       ing  upon  support  for that protocol being built into curl to avoid an\n"
"       error.\n"
"\n"
, stdout);