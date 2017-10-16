"              (HTTP)  Enables  GSS-Negotiate authentication. The GSS-Negotiate\n"
"              method was designed by Microsoft and is used in their web appli-\n"
"              cations.  It  is  primarily  meant  as  a  support for Kerberos5\n"
, stdout);
 fputs(
"              authentication but may be also used along with another authenti-\n"
"              cation method. For more information see IETF draft draft-brezak-\n"
"              spnego-http-04.txt.\n"
"\n"
"              If you want to enable Negotiate for your  proxy  authentication,\n"
"              then use --proxy-negotiate.\n"
"\n"
"              This  option  requires a library built with GSSAPI support. This\n"
"              is not very common. Use -V/--version to see if your version sup-\n"
