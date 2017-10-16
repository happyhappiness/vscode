 fputs(
"              vided  private  key  is.  DER, PEM and ENG are supported. If not\n"
"              specified, PEM is assumed.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       --krb <level>\n"
"              (FTP)  Enable Kerberos authentication and use. The level must be\n"
"              entered and should be one of ’clear’, ’safe’, ’confidential’  or\n"
"              ’private’.  Should  you  use  a  level that is not one of these,\n"
, stdout);
 fputs(
"              ’private’ will instead be used.\n"
"\n"
"              This option requires that the library was built  with  kerberos4\n"
"              or  GSSAPI (GSS-Negotiate) support. This is not very common. Use\n"
"              -V/--version to see if your curl supports it.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -K/--config <config file>\n"
"              Specify  which config file to read curl arguments from. The con‐\n"
, stdout);
