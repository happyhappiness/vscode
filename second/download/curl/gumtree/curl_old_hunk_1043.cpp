"  Netscape's \"Netscape Directory SDK 3.0 for C Programmer's Guide Chapter 10:\n"
"  Working with LDAP URLs\":\n"
, stdout);
 fputs(
"  http://developer.netscape.com/docs/manuals/dirsdk/csdk30/url.htm\n"
"\n"
"  RFC 2255, \"The LDAP URL Format\" http://curl.haxx.se/rfc/rfc2255.txt\n"
"\n"
"  To show you an example, this is how I can get all people from my local LDAP\n"
"  server that has a certain sub-domain in their email address:\n"
"\n"
"        curl -B \"ldap://ldap.frontec.se/o=frontec??sub?mail=*sth.frontec.se\"\n"
"\n"
