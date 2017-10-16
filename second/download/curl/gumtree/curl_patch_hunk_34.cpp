 "        curl dict://dict.org/show:strat\n"
 "\n"
 "  Authentication is still missing (but this is not required by the RFC)\n"
 "\n"
 "LDAP\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  If you have installed the OpenLDAP library, curl can take advantage of it\n"
 "  and offer ldap:// support.\n"
 "\n"
 "  LDAP is a complex thing and writing an LDAP query is not an easy task. I do\n"
 "  advice you to dig up the syntax description for that elsewhere. Two places\n"
 "  that might suit you are:\n"
 "\n"
 "  Netscape's \"Netscape Directory SDK 3.0 for C Programmer's Guide Chapter 10:\n"
 "  Working with LDAP URLs\":\n"
 "  http://developer.netscape.com/docs/manuals/dirsdk/csdk30/url.htm\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  RFC 2255, \"The LDAP URL Format\" http://www.rfc-editor.org/rfc/rfc2255.txt\n"
 "\n"
 "  To show you an example, this is now I can get all people from my local LDAP\n"
 "  server that has a certain sub-domain in their email address:\n"
 "\n"
 "        curl -B \"ldap://ldap.frontec.se/o=frontec??sub?mail=*sth.frontec.se\"\n"
