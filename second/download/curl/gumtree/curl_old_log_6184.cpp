fputs(
"   HTTP offers many different methods of authentication and curl supports\n"
"   several: Basic, Digest, NTLM and Negotiate. Without telling which method to\n"
"   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
"   ones out of the ones that the server accepts for the given URL, by using\n"
"   --anyauth.\n"
"\n"
"   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
"   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
, stdout);