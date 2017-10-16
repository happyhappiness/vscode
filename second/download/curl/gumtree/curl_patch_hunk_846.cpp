 "\n"
 , stdout);
  fputs(
 "        curl -u name:passwd http://machine.domain/full/path/to/file\n"
 "\n"
 "   HTTP offers many different methods of authentication and curl supports\n"
-"   several: Basic, Digest, NTLM and Negotiate. Without telling which method to\n"
-"   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
-"   ones out of the ones that the server accepts for the given URL, by using\n"
-"   --anyauth.\n"
+"   several: Basic, Digest, NTLM and Negotiate (SPNEGO). Without telling which\n"
+"   method to use, curl defaults to Basic. You can also ask curl to pick the\n"
+"   most secure ones out of the ones that the server accepts for the given URL,\n"
+"   by using --anyauth.\n"
 "\n"
 "   NOTE! According to the URL specification, HTTP URLs can not contain a user\n"
 , stdout);
  fputs(
 "   and password, so that style will not work when using curl via a proxy, even\n"
 "   though curl allows it at other times. When using a proxy, you _must_ use\n"
