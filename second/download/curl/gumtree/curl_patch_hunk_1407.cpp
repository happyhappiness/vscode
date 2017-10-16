 "  While -d uses the application/x-www-form-urlencoded mime-type, generally\n"
 "  understood by CGI's and similar, curl also supports the more capable\n"
 "  multipart/form-data type. This latter type supports things like file upload.\n"
 "\n"
 "  -F accepts parameters like -F \"name=contents\". If you want the contents to\n"
 "  be read from a file, use <@filename> as contents. When specifying a file,\n"
-"  you can also specify which content type the file is, by appending\n"
+"  you can also specify the file content type by appending ';type=<mime type>'\n"
 );
  puts(
-"  ';type=<mime type>' to the file name. You can also post contents of several\n"
-"  files in one field. So that the field name 'coolfiles' can be sent three\n"
-"  files with different content types in a manner similar to:\n"
+"  to the file name. You can also post the contents of several files in one field.\n"
+"  For example, the field name 'coolfiles' is used to send three  files, with\n"
+"  different content types using the following syntax:\n"
 "\n"
 "        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
 "        http://www.post.com/postit.cgi\n"
 "\n"
-"  If content-type is not specified, curl will try to guess from the extension\n"
-"  (it only knows a few), or use the previously specified type (from an earlier\n"
+"  If the content-type is not specified, curl will try to guess from the file\n"
+"  extension  (it only knows a few), or use the previously specified type\n"
 );
  puts(
-"  file if several files are specified in a list) or finally using the default\n"
-"  type 'text/plain'.\n"
+"  (from an earlier file if several files are specified in a list) or else it\n"
+"  will  using the default type 'text/plain'.\n"
 "\n"
 "  Emulate a fill-in form with -F. Let's say you fill in three fields in a\n"
 "  form. One field is a file name which to post, one field is your name and one\n"
 "  field is a file description. We want to post the file we have written named\n"
 "  \"cooltext.txt\". To let curl do the posting of this data instead of your\n"
-"  favourite browser, you have to check out the HTML of the form page to get to\n"
 );
  puts(
-"  know the names of the input fields. In our example, the input field names are\n"
+"  favourite browser, you have to read the HTML source of the form page and find\n"
+"  the names of the input fields. In our example, the input field names are\n"
 "  'file', 'yourname' and 'filedescription'.\n"
 "\n"
 "        curl -F \"file=@cooltext.txt\" -F \"yourname=Daniel\" \\\n"
 "             -F \"filedescription=Cool text file with cool text inside\" \\\n"
 "             http://www.post.com/postit.cgi\n"
 "\n"
-"  So, to send two files in one post you can do it in two ways:\n"
+"  To send two files in one post you can do it in two ways:\n"
 "\n"
+);
+ puts(
 "  1. Send multiple files in a single \"field\" with a single field name:\n"
 " \n"
 "        curl -F \"pictures=@dog.gif,cat.gif\" \n"
 " \n"
-);
- puts(
 "  2. Send two fields with two field names: \n"
 "\n"
 "        curl -F \"docpicture=@dog.gif\" -F \"catpicture=@cat.gif\" \n"
 "\n"
-"REFERER\n"
+"REFERRER\n"
 "\n"
 "  A HTTP request has the option to include information about which address\n"
-"  that referred to actual page, and curl allows the user to specify that\n"
-"  referrer to get specified on the command line. It is especially useful to\n"
+"  that referred to actual page.  Curl allows you to specify the\n"
+"  referrer to be used on the command line. It is especially useful to\n"
+);
+ puts(
 "  fool or trick stupid servers or CGI scripts that rely on that information\n"
 "  being available or contain certain data.\n"
 "\n"
-);
- puts(
 "        curl -e www.coolsite.com http://www.showme.com/\n"
 "\n"
 "  NOTE: The referer field is defined in the HTTP spec to be a full URL.\n"
 "\n"
 "USER AGENT\n"
 "\n"
 "  A HTTP request has the option to include information about the browser\n"
 "  that generated the request. Curl allows it to be specified on the command\n"
 "  line. It is especially useful to fool or trick stupid servers or CGI\n"
+);
+ puts(
 "  scripts that only accept certain browsers.\n"
 "\n"
 "  Example:\n"
 "\n"
 "  curl -A 'Mozilla/3.0 (Win95; I)' http://www.nationsbank.com/\n"
 "\n"
-);
- puts(
 "  Other common strings:\n"
 "    'Mozilla/3.0 (Win95; I)'     Netscape Version 3 for Windows 95\n"
 "    'Mozilla/3.04 (Win95; U)'    Netscape Version 3 for Windows 95\n"
 "    'Mozilla/2.02 (OS/2; U)'     Netscape Version 2 for OS/2\n"
 "    'Mozilla/4.04 [en] (X11; U; AIX 4.2; Nav)'           NS for AIX\n"
 "    'Mozilla/4.05 [en] (X11; U; Linux 2.0.32 i586)'      NS for Linux\n"
 "\n"
-"  Note that Internet Explorer tries hard to be compatible in every way:\n"
-"    'Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)'    MSIE for W95\n"
 );
  puts(
+"  Note that Internet Explorer tries hard to be compatible in every way:\n"
+"    'Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)'    MSIE for W95\n"
 "\n"
 "  Mozilla is not the only possible User-Agent name:\n"
 "    'Konqueror/1.0'             KDE File Manager desktop client\n"
 "    'Lynx/2.7.1 libwww-FM/2.14' Lynx command line browser\n"
 "\n"
 "COOKIES\n"
 "\n"
 "  Cookies are generally used by web servers to keep state information at the\n"
 "  client's side. The server sets cookies by sending a response line in the\n"
-"  headers that looks like 'Set-Cookie: <data>' where the data part then\n"
-"  typically contains a set of NAME=VALUE pairs (separated by semicolons ';'\n"
 );
  puts(
+"  headers that looks like 'Set-Cookie: <data>' where the data part then\n"
+"  typically contains a set of NAME=VALUE pairs (separated by semicolons ';'\n"
 "  like \"NAME1=VALUE1; NAME2=VALUE2;\"). The server can also specify for what\n"
 "  path the \"cookie\" should be used for (by specifying \"path=value\"), when the\n"
 "  cookie should expire (\"expire=DATE\"), for what domain to use it\n"
 "  (\"domain=NAME\") and if it should be used on secure connections only\n"
 "  (\"secure\").\n"
 "\n"
+);
+ puts(
 "  If you've received a page from a server that contains a header like:\n"
 "        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
 "\n"
-);
- puts(
 "  it means the server wants that first pair passed on when we get anything in\n"
 "  a path beginning with \"/foo\".\n"
 "\n"
 "  Example, get a page that wants my name passed in a cookie:\n"
 "\n"
 "        curl -b \"name=Daniel\" www.sillypage.com\n"
 "\n"
 "  Curl also has the ability to use previously received cookies in following\n"
 "  sessions. If you get cookies from a server and store them in a file in a\n"
+);
+ puts(
 "  manner similar to:\n"
 "\n"
 "        curl --dump-header headers www.example.com\n"
 "\n"
-);
- puts(
 "  ... you can then in a second connect to that (or another) site, use the\n"
 "  cookies from the 'headers' file like:\n"
 "\n"
 "        curl -b headers www.example.com\n"
 "\n"
 "  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
 "  you can make curl follow a location: (which often is used in combination\n"
 "  with cookies). So that if a site sends cookies and a location, you can\n"
-"  use a non-existing file to trig the cookie awareness like:\n"
-"\n"
-"        curl -L -b empty-file www.example.com\n"
-"\n"
 );
  puts(
+"  use a non-existing file to trigger the cookie awareness like:\n"
+"\n"
+"        curl -L -b empty.txt www.example.com\n"
+"\n"
 "  The file to read cookies from must be formatted using plain HTTP headers OR\n"
 "  as netscape's cookie file. Curl will determine what kind it is based on the\n"
-"  file contents.\n"
+"  file contents.  In the above command, curl will parse the header and store\n"
+"  the cookies received from www.example.com.  curl will send to the server the\n"
+"  stored cookies which match the request as it follows the location.  The\n"
+);
+ puts(
+"  file \"empty.txt\" may be a non-existant file.\n"
+"  \n"
 "\n"
 "PROGRESS METER\n"
 "\n"
 "  The progress meter exists to show a user that something actually is\n"
 "  happening. The different fields in the output have the following meaning:\n"
 "\n"
 "  % Total    % Received % Xferd  Average Speed          Time             Curr.\n"
 "                                 Dload  Upload Total    Current  Left    Speed\n"
-);
- puts(
 "  0  151M    0 38608    0     0   9406      0  4:41:43  0:00:04  4:41:39  9287\n"
 "\n"
 "  From left-to-right:\n"
+);
+ puts(
 "   %             - percentage completed of the whole transfer\n"
 "   Total         - total size of the whole expected transfer\n"
 "   %             - percentage completed of the download\n"
 "   Received      - currently downloaded amount of bytes\n"
 "   %             - percentage completed of the upload\n"
 "   Xferd         - currently uploaded amount of bytes\n"
 "   Average Speed\n"
-);
- puts(
 "   Dload         - the average transfer speed of the download\n"
 "   Average Speed\n"
 "   Upload        - the average transfer speed of the upload\n"
+);
+ puts(
 "   Time Total    - expected time to complete the operation\n"
 "   Time Current  - time passed since the invoke\n"
 "   Time Left     - expected time left to completetion\n"
 "   Curr.Speed    - the average transfer speed the last 5 seconds (the first\n"
 "                   5 seconds of a transfer is based on less time of course.)\n"
 "\n"
-);
- puts(
 "  The -# option will display a totally different progress bar that doesn't\n"
 "  need much explanation!\n"
 "\n"
 "SPEED LIMIT\n"
 "\n"
-"  Curl offers the user to set conditions regarding transfer speed that must\n"
-"  be met to let the transfer keep going. By using the switch -y and -Y you\n"
-"  can make curl abort transfers if the transfer speed doesn't exceed your\n"
-"  given lowest limit for a specified time.\n"
+);
+ puts(
+"  Curl allows the user to set the transfer speed conditions that must be met\n"
+"  to let the transfer keep going. By using the switch -y and -Y you\n"
+"  can make curl abort transfers if the transfer speed is below the specified\n"
+"  lowest limit for a specified time.\n"
 "\n"
-"  To let curl abandon downloading this page if its slower than 3000 bytes per\n"
+"  To have curl abort the download if the speed is slower than 3000 bytes per\n"
 "  second for 1 minute, run:\n"
 "\n"
-);
- puts(
 "        curl -y 3000 -Y 60 www.far-away-site.com\n"
 "\n"
 "  This can very well be used in combination with the overall time limit, so\n"
+);
+ puts(
 "  that the above operatioin must be completed in whole within 30 minutes:\n"
 "\n"
 "        curl -m 1800 -y 3000 -Y 60 www.far-away-site.com\n"
 "\n"
 "CONFIG FILE\n"
 "\n"
 "  Curl automatically tries to read the .curlrc file (or _curlrc file on win32\n"
 "  systems) from the user's home dir on startup.\n"
 "\n"
 "  The config file could be made up with normal command line switches, but you\n"
-);
- puts(
 "  can also specify the long options without the dashes to make it more\n"
 "  readable. You can separate the options and the parameter with spaces, or\n"
+);
+ puts(
 "  with = or :. Comments can be used within the file. If the first letter on a\n"
 "  line is a '#'-letter the rest of the line is treated as a comment.\n"
 "\n"
 "  If you want the parameter to contain spaces, you must inclose the entire\n"
 "  parameter within double quotes (\"). Within those quotes, you specify a\n"
 "  quote as \\\".\n"
 "\n"
-);
- puts(
 "  NOTE: You must specify options and their arguments on the same line.\n"
 "\n"
 "  Example, set default time out and proxy in a config file:\n"
 "\n"
 "        # We want a 30 minute timeout:\n"
 "        -m 1800\n"
+);
+ puts(
 "        # ... and we use a proxy for all accesses:\n"
 "        proxy = proxy.our.domain.com:8080\n"
 "\n"
 "  White spaces ARE significant at the end of lines, but all white spaces\n"
 "  leading up to the first characters of each line are ignored.\n"
 "\n"
 "  Prevent curl from reading the default file by using -q as the first command\n"
-);
- puts(
 "  line parameter, like:\n"
 "\n"
 "        curl -q www.thatsite.com\n"
 "\n"
 "  Force curl to get and display a local help page in case it is invoked\n"
 "  without URL by making a config file similar to:\n"
 "\n"
+);
+ puts(
 "        # default url to get\n"
 "        url = \"http://help.with.curl.com/curlhelp.html\"\n"
 "\n"
 "  You can specify another config file to be read by using the -K/--config\n"
 "  flag. If you set config file name to \"-\" it'll read the config from stdin,\n"
 "  which can be handy if you want to hide options from being visible in process\n"
-);
- puts(
 "  tables etc:\n"
 "\n"
 "        echo \"user = user:passwd\" | curl -K - http://that.secret.site.com\n"
 "\n"
 "EXTRA HEADERS\n"
 "\n"
 "  When using curl in your own very special programs, you may end up needing\n"
+);
+ puts(
 "  to pass on your own custom headers when getting a web page. You can do\n"
 "  this by using the -H flag.\n"
 "\n"
 "  Example, send the header \"X-you-and-me: yes\" to the server when getting a\n"
 "  page:\n"
 "\n"
 "        curl -H \"X-you-and-me: yes\" www.love.com\n"
 "\n"
 "  This can also be useful in case you want curl to send a different text in a\n"
-);
- puts(
 "  header than it normally does. The -H header you specify then replaces the\n"
 "  header curl would normally send. If you replace an internal header with an\n"
+);
+ puts(
 "  empty one, you prevent that header from being sent. To prevent the Host:\n"
 "  header from being used:\n"
 "\n"
 "        curl -H \"Host:\" www.server.com\n"
 "\n"
 "FTP and PATH NAMES\n"
 "\n"
 "  Do note that when getting files with the ftp:// URL, the given path is\n"
 "  relative the directory you enter. To get the file 'README' from your home\n"
 "  directory at your ftp site, do:\n"
 "\n"
-);
- puts(
 "        curl ftp://user:passwd@my.site.com/README\n"
 "\n"
 "  But if you want the README file from the root directory of that very same\n"
+);
+ puts(
 "  site, you need to specify the absolute file name:\n"
 "\n"
 "        curl ftp://user:passwd@my.site.com//README\n"
 "\n"
 "  (I.e with an extra slash in front of the file name.)\n"
 "\n"
 "FTP and firewalls\n"
 "\n"
 "  The FTP protocol requires one of the involved parties to open a second\n"
 "  connction as soon as data is about to get transfered. There are two ways to\n"
 "  do this.\n"
 "\n"
-);
- puts(
 "  The default way for curl is to issue the PASV command which causes the\n"
 "  server to open another port and await another connection performed by the\n"
+);
+ puts(
 "  client. This is good if the client is behind a firewall that don't allow\n"
 "  incoming connections.\n"
 "\n"
 "        curl ftp.download.com\n"
 "\n"
 "  If the server for example, is behind a firewall that don't allow connections\n"
 "  on other ports than 21 (or if it just doesn't support the PASV command), the\n"
-);
- puts(
 "  other way to do it is to use the PORT command and instruct the server to\n"
 "  connect to the client on the given (as parameters to the PORT command) IP\n"
 "  number and port.\n"
 "\n"
+);
+ puts(
 "  The -P flag to curl supports a few different options. Your machine may have\n"
 "  several IP-addresses and/or network interfaces and curl allows you to select\n"
 "  which of them to use. Default address can also be used:\n"
 "\n"
 "        curl -P - ftp.download.com\n"
 "\n"
-);
- puts(
 "  Download with PORT but use the IP address of our 'le0' interface (this does\n"
 "  not work on windows):\n"
 "\n"
 "        curl -P le0 ftp.download.com\n"
 "\n"
 "  Download with PORT but use 192.168.0.10 as our IP address to use:\n"
 "\n"
+);
+ puts(
 "        curl -P 192.168.0.10 ftp.download.com\n"
 "\n"
 "NETWORK INTERFACE\n"
 "\n"
 "  Get a web page from a server using a specified port for the interface:\n"
 "\n"
