fputs(
"       --krb4 <level>\n"
"              (FTP) Enable kerberos4 authentication and use. The level must be\n"
"              entered and should be one of 'clear', 'safe', 'confidential'  or\n"
"              'private'.  Should  you  use  a  level that is not one of these,\n"
"              'private' will instead be used.\n"
"\n"
"              This option requires that the library was built  with  kerberos4\n"
"              support.  This  is  not  very common. Use -V/--version to see if\n"
, stdout);