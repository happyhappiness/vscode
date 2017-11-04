fputs(
"  You also can use authentication when accessing LDAP catalog:\n"
"\n"
"      curl -u user:passwd \"ldap://ldap.frontec.se/o=frontec??sub?mail=*\"\n"
"      curl \"ldap://user:passwd@ldap.frontec.se/o=frontec??sub?mail=*\"\n"
"\n"
"  By default, if user and password provided, OpenLDAP/WinLDAP will use basic\n"
"  authentication. On Windows you can control this behavior by providing \n"
"  one of --basic, --ntlm or --digest option in curl command line\n"
"\n"
, stdout);