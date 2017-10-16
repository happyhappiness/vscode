 "  If you have installed the OpenLDAP library, curl can take advantage of it\n"
 "  and offer ldap:// support.\n"
 "\n"
 "  LDAP is a complex thing and writing an LDAP query is not an easy task. I do\n"
 );
  puts(
-"  advice you to dig up the syntax description for that elsewhere, RFC 1959 if\n"
-"  no other place is better.\n"
+"  advice you to dig up the syntax description for that elsewhere. Two places\n"
+"  that might suit you are:\n"
+"\n"
+"  Netscape's \"Netscape Directory SDK 3.0 for C Programmer's Guide Chapter 10:\n"
+"  Working with LDAP URLs\":\n"
+"  http://developer.netscape.com/docs/manuals/dirsdk/csdk30/url.htm\n"
+"\n"
+"  RFC 2255, \"The LDAP URL Format\" http://www.rfc-editor.org/rfc/rfc2255.txt\n"
 "\n"
 "  To show you an example, this is now I can get all people from my local LDAP\n"
 "  server that has a certain sub-domain in their email address:\n"
 "\n"
+);
+ puts(
 "        curl -B \"ldap://ldap.frontec.se/o=frontec??sub?mail=*sth.frontec.se\"\n"
 "\n"
 "  If I want the same info in HTML format, I can get it by not using the -B\n"
 "  (enforce ASCII) flag.\n"
 "\n"
 "ENVIRONMENT VARIABLES\n"
 "\n"
-);
- puts(
 "  Curl reads and understands the following environment variables:\n"
 "\n"
-"        HTTP_PROXY, HTTPS_PROXY, FTP_PROXY, GOPHER_PROXY\n"
+"        http_proxy, HTTPS_PROXY, FTP_PROXY, GOPHER_PROXY\n"
 "\n"
 "  They should be set for protocol-specific proxies. General proxy should be\n"
 "  set with\n"
 "        \n"
 "        ALL_PROXY\n"
 "\n"
+);
+ puts(
 "  A comma-separated list of host names that shouldn't go through any proxy is\n"
 "  set in (only an asterisk, '*' matches all hosts)\n"
 "\n"
 "        NO_PROXY\n"
 "\n"
 "  If a tail substring of the domain-path for a host matches one of these\n"
-);
- puts(
 "  strings, transactions with that node will not be proxied.\n"
 "\n"
 "\n"
 "  The usage of the -x/--proxy flag overrides the environment variables.\n"
 "\n"
 "NETRC\n"
 "\n"
 "  Unix introduced the .netrc concept a long time ago. It is a way for a user\n"
+);
+ puts(
 "  to specify name and password for commonly visited ftp sites in a file so\n"
 "  that you don't have to type them in each time you visit those sites. You\n"
 "  realize this is a big security risk if someone else gets hold of your\n"
-);
- puts(
 "  passwords, so therefor most unix programs won't read this file unless it is\n"
 "  only readable by yourself (curl doesn't care though).\n"
 "\n"
-"  Curl supports .netrc files if told so (using the -n/--netrc option). This is\n"
-"  not restricted to only ftp, but curl can use it for all protocols where\n"
-"  authentication is used.\n"
+"  Curl supports .netrc files if told so (using the -n/--netrc and\n"
+"  --netrc-optional options). This is not restricted to only ftp,\n"
+);
+ puts(
+"  but curl can use it for all protocols where authentication is used.\n"
 "\n"
 "  A very simple .netrc file could look something like:\n"
 "\n"
 "        machine curl.haxx.se login iamdaniel password mysecret\n"
 "\n"
 "CUSTOM OUTPUT\n"
 "\n"
-);
- puts(
 "  To better allow script programmers to get to know about the progress of\n"
 "  curl, the -w/--write-out option was introduced. Using this, you can specify\n"
 "  what information from the previous transfer you want to extract.\n"
 "\n"
+);
+ puts(
 "  To display the amount of bytes downloaded together with some text and an\n"
 "  ending newline:\n"
 "\n"
 "        curl -w 'We downloaded %{size_download} bytes\\n' www.download.com\n"
 "\n"
 "KERBEROS4 FTP TRANSFER\n"
 "\n"
 "  Curl supports kerberos4 for FTP transfers. You need the kerberos package\n"
-);
- puts(
 "  installed and used at curl build time for it to be used.\n"
 "\n"
 "  First, get the krb-ticket the normal way, like with the kauth tool. Then use\n"
 "  curl in way similar to:\n"
 "\n"
+);
+ puts(
 "        curl --krb4 private ftp://krb4site.com -u username:fakepwd\n"
 "\n"
 "  There's no use for a password on the -u switch, but a blank one will make\n"
 "  curl ask for one and you already entered the real password to kauth.\n"
 "\n"
 "TELNET\n"
 "\n"
 "  The curl telnet support is basic and very easy to use. Curl passes all data\n"
-);
- puts(
 "  passed to it on stdin to the remote server. Connect to a remote telnet\n"
 "  server using a command line similar to:\n"
 "\n"
 "        curl telnet://remote.server.com\n"
 "\n"
+);
+ puts(
 "  And enter the data to pass to the server on stdin. The result will be sent\n"
 "  to stdout or to the file you specify with -o.\n"
 "\n"
 "  You might want the -N/--no-buffer option to switch off the buffered output\n"
 "  for slow connections or similar.\n"
 "\n"
-"  NOTE: the telnet protocol does not specify any way to login with a specified\n"
+"  Pass options to the telnet protocol negotiation, by using the -t option. To\n"
+"  tell the server we use a vt100 terminal, try something like:\n"
+"\n"
+"        curl -tTTYPE=vt100 telnet://remote.server.com\n"
+"\n"
+"  Other interesting options for it -t include:\n"
+"\n"
 );
  puts(
+"   - XDISPLOC=<X display> Sets the X display location.\n"
+"\n"
+"   - NEW_ENV=<var,val> Sets an environment variable.\n"
+"\n"
+"  NOTE: the telnet protocol does not specify any way to login with a specified\n"
 "  user and password so curl can't do that automatically. To do that, you need\n"
 "  to track when the login prompt is received and send the username and\n"
 "  password accordingly.\n"
 "\n"
 "PERSISTANT CONNECTIONS\n"
 "\n"
 "  Specifying multiple files on a single command line will make curl transfer\n"
+);
+ puts(
 "  all of them, one after the other in the specified order.\n"
 "\n"
 "  libcurl will attempt to use persistant connections for the transfers so that\n"
 "  the second transfer to the same host can use the same connection that was\n"
-);
- puts(
 "  already initiated and was left open in the previous transfer. This greatly\n"
 "  decreases connection time for all but the first transfer and it makes a far\n"
 "  better use of the network.\n"
 "\n"
 "  Note that curl cannot use persistant connections for transfers that are used\n"
+);
+ puts(
 "  in subsequence curl invokes. Try to stuff as many URLs as possible on the\n"
 "  same command line if they are using the same host, as that'll make the\n"
 "  transfers faster. If you use a http proxy for file transfers, practicly\n"
-);
- puts(
 "  all transfers will be persistant.\n"
 "\n"
 "  Persistant connections were introduced in curl 7.7.\n"
 "\n"
 "MAILING LISTS\n"
 "\n"
 "  For your convenience, we have several open mailing lists to discuss curl,\n"
-"  its development and things relevant to this.\n"
+"  its development and things relevant to this. Get all info at\n"
+);
+ puts(
+"  http://curl.haxx.se/mail/. The lists available are:\n"
+"\n"
+"  curl-users\n"
+"\n"
+"    Users of the command line tool. How to use it, what doesn't work, new\n"
+"    features, related tools, questions, news, installations, compilations,\n"
+"    running, porting etc.\n"
+"\n"
+"  curl-library\n"
 "\n"
-"  To subscribe to the main curl list, mail curl-request@contactor.se with\n"
-"  \"subscribe <fill in your email address>\" in the body.\n"
+"    Developers using or developing libcurl. Bugs, extensions, improvements.\n"
 "\n"
-"  To subscribe to the curl-library users/deverlopers list, follow the\n"
-"  instructions at http://curl.haxx.se/mail/\n"
+"  curl-announce\n"
+"\n"
+"    Low-traffic. Only announcements of new public versions.\n"
+"\n"
+"  curl-and-PHP\n"
 "\n"
 );
  puts(
-"  To subscribe to the curl-announce list, to only get information about new\n"
-"  releases, follow the instructions at http://curl.haxx.se/mail/\n"
+"    Using the curl functions in PHP. Everything curl with a PHP angle. Or PHP\n"
+"    with a curl angle.\n"
+"\n"
+"  curl-commits\n"
+"\n"
+"    Receives notifications on all CVS commits done to the curl source module.\n"
+"    This can become quite a large amount of mails during intense development,\n"
+"    be aware. This is for us who liks email...\n"
 "\n"
-"  To subscribe to the curl-and-PHP list in which curl using with PHP is\n"
-"  discussed, follow the instructions at http://curl.haxx.se/mail/\n"
+"  curl-www-commits\n"
+"\n"
+"    Receives notifications on all CVS commits done to the curl www module\n"
+"    (basicly the web site).  This can become quite a large amount of mails\n"
+);
+ puts(
+"    during intense changing, be aware. This is for us who liks email...\n"
 "\n"
 "  Please direct curl questions, feature requests and trouble reports to one of\n"
 "  these mailing lists instead of mailing any individual.\n"
  ) ;
 }
