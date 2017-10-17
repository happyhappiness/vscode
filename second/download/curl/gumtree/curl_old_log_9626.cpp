fputs(
"  addresses can also be specified directly in URLs using the syntax:\n"
"\n"
"    http://[2001:1890:1112:1::20]/overview.html\n"
"\n"
"  When this style is used, the -g option must be given to stop curl from\n"
"  interpreting the square brackets as special globbing characters.  Link local\n"
"  and site local addresses including a scope identifier, such as fe80::1234%1,\n"
"  may also be used, but the scope portion must be numeric or match an existing\n"
, stdout);