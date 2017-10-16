 "\n"
 "        curl -F \"docpicture=@dog.gif\" -F \"catpicture=@cat.gif\" \n"
 "\n"
 "REFERRER\n"
 "\n"
 "  A HTTP request has the option to include information about which address\n"
-);
- puts(
 "  that referred to actual page.  Curl allows you to specify the\n"
+, stdout);
+ fputs(
 "  referrer to be used on the command line. It is especially useful to\n"
 "  fool or trick stupid servers or CGI scripts that rely on that information\n"
 "  being available or contain certain data.\n"
 "\n"
 "        curl -e www.coolsite.com http://www.showme.com/\n"
 "\n"
 "  NOTE: The referer field is defined in the HTTP spec to be a full URL.\n"
 "\n"
 "USER AGENT\n"
 "\n"
 "  A HTTP request has the option to include information about the browser\n"
-);
- puts(
 "  that generated the request. Curl allows it to be specified on the command\n"
+, stdout);
+ fputs(
 "  line. It is especially useful to fool or trick stupid servers or CGI\n"
 "  scripts that only accept certain browsers.\n"
 "\n"
 "  Example:\n"
 "\n"
 "  curl -A 'Mozilla/3.0 (Win95; I)' http://www.nationsbank.com/\n"
 "\n"
 "  Other common strings:\n"
 "    'Mozilla/3.0 (Win95; I)'     Netscape Version 3 for Windows 95\n"
 "    'Mozilla/3.04 (Win95; U)'    Netscape Version 3 for Windows 95\n"
 "    'Mozilla/2.02 (OS/2; U)'     Netscape Version 2 for OS/2\n"
-);
- puts(
 "    'Mozilla/4.04 [en] (X11; U; AIX 4.2; Nav)'           NS for AIX\n"
+, stdout);
+ fputs(
 "    'Mozilla/4.05 [en] (X11; U; Linux 2.0.32 i586)'      NS for Linux\n"
 "\n"
 "  Note that Internet Explorer tries hard to be compatible in every way:\n"
 "    'Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)'    MSIE for W95\n"
 "\n"
 "  Mozilla is not the only possible User-Agent name:\n"
 "    'Konqueror/1.0'             KDE File Manager desktop client\n"
 "    'Lynx/2.7.1 libwww-FM/2.14' Lynx command line browser\n"
 "\n"
 "COOKIES\n"
 "\n"
-);
- puts(
 "  Cookies are generally used by web servers to keep state information at the\n"
+, stdout);
+ fputs(
 "  client's side. The server sets cookies by sending a response line in the\n"
 "  headers that looks like 'Set-Cookie: <data>' where the data part then\n"
 "  typically contains a set of NAME=VALUE pairs (separated by semicolons ';'\n"
 "  like \"NAME1=VALUE1; NAME2=VALUE2;\"). The server can also specify for what\n"
 "  path the \"cookie\" should be used for (by specifying \"path=value\"), when the\n"
-);
- puts(
 "  cookie should expire (\"expire=DATE\"), for what domain to use it\n"
+, stdout);
+ fputs(
 "  (\"domain=NAME\") and if it should be used on secure connections only\n"
 "  (\"secure\").\n"
 "\n"
 "  If you've received a page from a server that contains a header like:\n"
 "        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
 "\n"
