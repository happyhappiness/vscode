fputs(
"        curl http://name:passwd@machine.domain/full/path/to/file\n"
"\n"
"   or specify user and password separately like in\n"
"\n"
"        curl -u name:passwd http://machine.domain/full/path/to/file\n"
"\n"
"   HTTP offers many different methods of authentication and curl supports\n"
"   several: Basic, Digest, NTLM and Negotiate (SPNEGO). Without telling which\n"
"   method to use, curl defaults to Basic. You can also ask curl to pick the\n"
"   most secure ones out of the ones that the server accepts for the given URL,\n"
, stdout);