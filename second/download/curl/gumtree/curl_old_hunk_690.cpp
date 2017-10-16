"                     in  the  Kerberos  service  ticket,  which is a matter of\n"
"                     realm policy.\n"
"\n"
"              always Unconditionally allow the server to delegate.\n"
"\n"
"       --digest\n"
"              (HTTP) Enables HTTP Digest authentication. This is a authentica-\n"
"              tion that prevents the password from being sent over the wire in\n"
"              clear text. Use this in combination with the normal  -u,  --user\n"
, stdout);
 fputs(
"              option to set user name and password. See also --ntlm, --negoti-\n"
"              ate and --anyauth for related options.\n"
"\n"
"              If this option is used several times, the following  occurrences\n"
"              make no difference.\n"
"\n"
"       --disable-eprt\n"
"              (FTP) Tell curl to disable the use of the EPRT and LPRT commands\n"
"              when doing active FTP transfers. Curl will normally always first\n"
, stdout);
 fputs(
