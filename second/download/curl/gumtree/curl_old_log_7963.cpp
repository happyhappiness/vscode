fputs(
"   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
"   ones out of the ones that the server accepts for the given URL, by using\n"
"   --anyauth.\n"
"\n"
"   NOTE! According to the URL specification, HTTP URLs can not contain a user\n"
"   and password, so that style will not work when using curl via a proxy, even\n"
"   though curl allows it at other times. When using a proxy, you _must_ use\n"
"   the -u style for user and password.\n"
"\n"
" HTTPS\n"
"\n"
, stdout);