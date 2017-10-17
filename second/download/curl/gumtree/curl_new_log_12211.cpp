fputs(
"   several: Basic, Digest, NTLM and Negotiate (SPNEGO). Without telling which\n"
"   method to use, curl defaults to Basic. You can also ask curl to pick the\n"
"   most secure ones out of the ones that the server accepts for the given URL,\n"
"   by using --anyauth.\n"
"\n"
"   NOTE! According to the URL specification, HTTP URLs can not contain a user\n"
"   and password, so that style will not work when using curl via a proxy, even\n"
"   though curl allows it at other times. When using a proxy, you _must_ use\n"
, stdout);