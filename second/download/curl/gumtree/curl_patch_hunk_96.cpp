 "   It is just like for FTP, but you may also want to specify and use\n"
 "   SSL-specific options for certificates etc.\n"
 "\n"
 " HTTP\n"
 "\n"
 "   The HTTP URL doesn't support user and password in the URL string. Curl\n"
-, stdout);
- fputs(
 "   does support that anyway to provide a ftp-style interface and thus you can\n"
 "   pick a file like:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl http://name:passwd@machine.domain/full/path/to/file\n"
 "\n"
 "   or specify user and password separately like in\n"
 "\n"
 "        curl -u name:passwd http://machine.domain/full/path/to/file\n"
 "\n"
 "   HTTP offers many different methods of authentication and curl supports\n"
 "   several: Basic, Digest, NTLM and Negotiate. Without telling which method to\n"
-, stdout);
- fputs(
 "   use, curl defaults to Basic. You can also ask curl to pick the most secure\n"
 "   ones out of the ones that the server accepts for the given URL, by using\n"
+, stdout);
+ fputs(
 "   --anyauth.\n"
 "\n"
 "   NOTE! Since HTTP URLs don't support user and password, you can't use that\n"
 "   style when using Curl via a proxy. You _must_ use the -u style fetch\n"
 "   during such circumstances.\n"
 "\n"
