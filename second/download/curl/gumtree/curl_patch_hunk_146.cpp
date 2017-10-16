 "  2. Send two fields with two field names: \n"
 "\n"
 , stdout);
  fputs(
 "        curl -F \"docpicture=@dog.gif\" -F \"catpicture=@cat.gif\" \n"
 "\n"
+"  To send a field value literally without interpreting a leading '@'\n"
+"  or '<', or an embedded ';type=', use --form-string instead of\n"
+"  -F. This is recommended when the value is obtained from a user or\n"
+"  some other unpredictable source. Under these circumstances, using\n"
+"  -F instead of --form-string would allow a user to trick curl into\n"
+"  uploading a file.\n"
+"\n"
 "REFERRER\n"
 "\n"
+, stdout);
+ fputs(
 "  A HTTP request has the option to include information about which address\n"
 "  that referred to actual page.  Curl allows you to specify the\n"
 "  referrer to be used on the command line. It is especially useful to\n"
 "  fool or trick stupid servers or CGI scripts that rely on that information\n"
 "  being available or contain certain data.\n"
 "\n"
 "        curl -e www.coolsite.com http://www.showme.com/\n"
 "\n"
-, stdout);
- fputs(
 "  NOTE: The referer field is defined in the HTTP spec to be a full URL.\n"
 "\n"
 "USER AGENT\n"
 "\n"
+, stdout);
+ fputs(
 "  A HTTP request has the option to include information about the browser\n"
 "  that generated the request. Curl allows it to be specified on the command\n"
 "  line. It is especially useful to fool or trick stupid servers or CGI\n"
 "  scripts that only accept certain browsers.\n"
 "\n"
 "  Example:\n"
 "\n"
 "  curl -A 'Mozilla/3.0 (Win95; I)' http://www.nationsbank.com/\n"
 "\n"
 "  Other common strings:\n"
-, stdout);
- fputs(
 "    'Mozilla/3.0 (Win95; I)'     Netscape Version 3 for Windows 95\n"
 "    'Mozilla/3.04 (Win95; U)'    Netscape Version 3 for Windows 95\n"
+, stdout);
+ fputs(
 "    'Mozilla/2.02 (OS/2; U)'     Netscape Version 2 for OS/2\n"
 "    'Mozilla/4.04 [en] (X11; U; AIX 4.2; Nav)'           NS for AIX\n"
 "    'Mozilla/4.05 [en] (X11; U; Linux 2.0.32 i586)'      NS for Linux\n"
 "\n"
 "  Note that Internet Explorer tries hard to be compatible in every way:\n"
 "    'Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)'    MSIE for W95\n"
 "\n"
-, stdout);
- fputs(
 "  Mozilla is not the only possible User-Agent name:\n"
 "    'Konqueror/1.0'             KDE File Manager desktop client\n"
+, stdout);
+ fputs(
 "    'Lynx/2.7.1 libwww-FM/2.14' Lynx command line browser\n"
 "\n"
 "COOKIES\n"
 "\n"
 "  Cookies are generally used by web servers to keep state information at the\n"
 "  client's side. The server sets cookies by sending a response line in the\n"
 "  headers that looks like 'Set-Cookie: <data>' where the data part then\n"
 "  typically contains a set of NAME=VALUE pairs (separated by semicolons ';'\n"
+"  like \"NAME1=VALUE1; NAME2=VALUE2;\"). The server can also specify for what\n"
 , stdout);
  fputs(
-"  like \"NAME1=VALUE1; NAME2=VALUE2;\"). The server can also specify for what\n"
 "  path the \"cookie\" should be used for (by specifying \"path=value\"), when the\n"
 "  cookie should expire (\"expire=DATE\"), for what domain to use it\n"
 "  (\"domain=NAME\") and if it should be used on secure connections only\n"
 "  (\"secure\").\n"
 "\n"
 "  If you've received a page from a server that contains a header like:\n"
 "        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
 "\n"
-, stdout);
- fputs(
 "  it means the server wants that first pair passed on when we get anything in\n"
 "  a path beginning with \"/foo\".\n"
 "\n"
+, stdout);
+ fputs(
 "  Example, get a page that wants my name passed in a cookie:\n"
 "\n"
 "        curl -b \"name=Daniel\" www.sillypage.com\n"
 "\n"
 "  Curl also has the ability to use previously received cookies in following\n"
 "  sessions. If you get cookies from a server and store them in a file in a\n"
 "  manner similar to:\n"
 "\n"
 "        curl --dump-header headers www.example.com\n"
 "\n"
-, stdout);
- fputs(
 "  ... you can then in a second connect to that (or another) site, use the\n"
 "  cookies from the 'headers' file like:\n"
 "\n"
 "        curl -b headers www.example.com\n"
 "\n"
+, stdout);
+ fputs(
 "  While saving headers to a file is a working way to store cookies, it is\n"
 "  however error-prone and not the preferred way to do this. Instead, make curl\n"
 "  save the incoming cookies using the well-known netscape cookie format like\n"
 "  this:\n"
 "\n"
 "        curl -c cookies.txt www.example.com\n"
 "\n"
-, stdout);
- fputs(
 "  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
 "  you can make curl follow a location: (which often is used in combination\n"
+, stdout);
+ fputs(
 "  with cookies). So that if a site sends cookies and a location, you can\n"
 "  use a non-existing file to trigger the cookie awareness like:\n"
 "\n"
 "        curl -L -b empty.txt www.example.com\n"
 "\n"
 "  The file to read cookies from must be formatted using plain HTTP headers OR\n"
 "  as netscape's cookie file. Curl will determine what kind it is based on the\n"
-, stdout);
- fputs(
 "  file contents.  In the above command, curl will parse the header and store\n"
 "  the cookies received from www.example.com.  curl will send to the server the\n"
+, stdout);
+ fputs(
 "  stored cookies which match the request as it follows the location.  The\n"
 "  file \"empty.txt\" may be a nonexistent file.\n"
 "\n"
 "  Alas, to both read and write cookies from a netscape cookie file, you can\n"
 "  set both -b and -c to use the same file:\n"
 "\n"
 "        curl -b cookies.txt -c cookies.txt www.example.com\n"
 "\n"
 "PROGRESS METER\n"
 "\n"
-, stdout);
- fputs(
 "  The progress meter exists to show a user that something actually is\n"
 "  happening. The different fields in the output have the following meaning:\n"
 "\n"
+, stdout);
+ fputs(
 "  % Total    % Received % Xferd  Average Speed          Time             Curr.\n"
 "                                 Dload  Upload Total    Current  Left    Speed\n"
 "  0  151M    0 38608    0     0   9406      0  4:41:43  0:00:04  4:41:39  9287\n"
 "\n"
 "  From left-to-right:\n"
 "   %             - percentage completed of the whole transfer\n"
-, stdout);
- fputs(
 "   Total         - total size of the whole expected transfer\n"
 "   %             - percentage completed of the download\n"
 "   Received      - currently downloaded amount of bytes\n"
+, stdout);
+ fputs(
 "   %             - percentage completed of the upload\n"
 "   Xferd         - currently uploaded amount of bytes\n"
 "   Average Speed\n"
 "   Dload         - the average transfer speed of the download\n"
 "   Average Speed\n"
 "   Upload        - the average transfer speed of the upload\n"
 "   Time Total    - expected time to complete the operation\n"
-, stdout);
- fputs(
 "   Time Current  - time passed since the invoke\n"
 "   Time Left     - expected time left to completion\n"
 "   Curr.Speed    - the average transfer speed the last 5 seconds (the first\n"
+, stdout);
+ fputs(
 "                   5 seconds of a transfer is based on less time of course.)\n"
 "\n"
 "  The -# option will display a totally different progress bar that doesn't\n"
 "  need much explanation!\n"
 "\n"
 "SPEED LIMIT\n"
 "\n"
 "  Curl allows the user to set the transfer speed conditions that must be met\n"
-, stdout);
- fputs(
 "  to let the transfer keep going. By using the switch -y and -Y you\n"
 "  can make curl abort transfers if the transfer speed is below the specified\n"
 "  lowest limit for a specified time.\n"
 "\n"
+, stdout);
+ fputs(
 "  To have curl abort the download if the speed is slower than 3000 bytes per\n"
 "  second for 1 minute, run:\n"
 "\n"
 "        curl -Y 3000 -y 60 www.far-away-site.com\n"
 "\n"
 "  This can very well be used in combination with the overall time limit, so\n"
 "  that the above operation must be completed in whole within 30 minutes:\n"
 "\n"
-, stdout);
- fputs(
 "        curl -m 1800 -Y 3000 -y 60 www.far-away-site.com\n"
 "\n"
 "  Forcing curl not to transfer data faster than a given rate is also possible,\n"
+, stdout);
+ fputs(
 "  which might be useful if you're using a limited bandwidth connection and you\n"
 "  don't want your transfer to use all of it (sometimes referred to as\n"
 "  \"bandwidth throttle\").\n"
 "\n"
 "  Make curl transfer data no faster than 10 kilobytes per second:\n"
 "\n"
 "        curl --limit-rate 10K www.far-away-site.com\n"
 "\n"
 "    or\n"
 "\n"
 "        curl --limit-rate 10240 www.far-away-site.com\n"
 "\n"
-, stdout);
- fputs(
 "  Or prevent curl from uploading data faster than 1 megabyte per second:\n"
 "\n"
 "        curl -T upload --limit-rate 1M ftp://uploadshereplease.com\n"
 "\n"
+, stdout);
+ fputs(
 "  When using the --limit-rate option, the transfer rate is regulated on a\n"
 "  per-second basis, which will cause the total transfer speed to become lower\n"
 "  than the given number. Sometimes of course substantially lower, if your\n"
 "  transfer stalls during periods.\n"
 "\n"
 "CONFIG FILE\n"
 "\n"
 "  Curl automatically tries to read the .curlrc file (or _curlrc file on win32\n"
-, stdout);
- fputs(
 "  systems) from the user's home dir on startup.\n"
 "\n"
 "  The config file could be made up with normal command line switches, but you\n"
+, stdout);
+ fputs(
 "  can also specify the long options without the dashes to make it more\n"
 "  readable. You can separate the options and the parameter with spaces, or\n"
 "  with = or :. Comments can be used within the file. If the first letter on a\n"
 "  line is a '#'-letter the rest of the line is treated as a comment.\n"
 "\n"
 "  If you want the parameter to contain spaces, you must inclose the entire\n"
-, stdout);
- fputs(
 "  parameter within double quotes (\"). Within those quotes, you specify a\n"
 "  quote as \\\".\n"
 "\n"
+, stdout);
+ fputs(
 "  NOTE: You must specify options and their arguments on the same line.\n"
 "\n"
 "  Example, set default time out and proxy in a config file:\n"
 "\n"
 "        # We want a 30 minute timeout:\n"
 "        -m 1800\n"
 "        # ... and we use a proxy for all accesses:\n"
 "        proxy = proxy.our.domain.com:8080\n"
 "\n"
 "  White spaces ARE significant at the end of lines, but all white spaces\n"
-, stdout);
- fputs(
 "  leading up to the first characters of each line are ignored.\n"
 "\n"
 "  Prevent curl from reading the default file by using -q as the first command\n"
+, stdout);
+ fputs(
 "  line parameter, like:\n"
 "\n"
 "        curl -q www.thatsite.com\n"
 "\n"
 "  Force curl to get and display a local help page in case it is invoked\n"
 "  without URL by making a config file similar to:\n"
 "\n"
 "        # default url to get\n"
 "        url = \"http://help.with.curl.com/curlhelp.html\"\n"
 "\n"
 "  You can specify another config file to be read by using the -K/--config\n"
-, stdout);
- fputs(
 "  flag. If you set config file name to \"-\" it'll read the config from stdin,\n"
 "  which can be handy if you want to hide options from being visible in process\n"
+, stdout);
+ fputs(
 "  tables etc:\n"
 "\n"
 "        echo \"user = user:passwd\" | curl -K - http://that.secret.site.com\n"
 "\n"
 "EXTRA HEADERS\n"
 "\n"
 "  When using curl in your own very special programs, you may end up needing\n"
 "  to pass on your own custom headers when getting a web page. You can do\n"
 "  this by using the -H flag.\n"
 "\n"
-, stdout);
- fputs(
 "  Example, send the header \"X-you-and-me: yes\" to the server when getting a\n"
 "  page:\n"
 "\n"
 "        curl -H \"X-you-and-me: yes\" www.love.com\n"
 "\n"
 "  This can also be useful in case you want curl to send a different text in a\n"
+, stdout);
+ fputs(
 "  header than it normally does. The -H header you specify then replaces the\n"
 "  header curl would normally send. If you replace an internal header with an\n"
 "  empty one, you prevent that header from being sent. To prevent the Host:\n"
 "  header from being used:\n"
 "\n"
-, stdout);
- fputs(
 "        curl -H \"Host:\" www.server.com\n"
 "\n"
 "FTP and PATH NAMES\n"
 "\n"
 "  Do note that when getting files with the ftp:// URL, the given path is\n"
 "  relative the directory you enter. To get the file 'README' from your home\n"
 "  directory at your ftp site, do:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl ftp://user:passwd@my.site.com/README\n"
 "\n"
 "  But if you want the README file from the root directory of that very same\n"
 "  site, you need to specify the absolute file name:\n"
 "\n"
 "        curl ftp://user:passwd@my.site.com//README\n"
 "\n"
-, stdout);
- fputs(
 "  (I.e with an extra slash in front of the file name.)\n"
 "\n"
 "FTP and firewalls\n"
 "\n"
 "  The FTP protocol requires one of the involved parties to open a second\n"
 "  connction as soon as data is about to get transfered. There are two ways to\n"
 "  do this.\n"
 "\n"
+, stdout);
+ fputs(
 "  The default way for curl is to issue the PASV command which causes the\n"
 "  server to open another port and await another connection performed by the\n"
 "  client. This is good if the client is behind a firewall that don't allow\n"
 "  incoming connections.\n"
 "\n"
-, stdout);
- fputs(
 "        curl ftp.download.com\n"
 "\n"
 "  If the server for example, is behind a firewall that don't allow connections\n"
 "  on other ports than 21 (or if it just doesn't support the PASV command), the\n"
+, stdout);
+ fputs(
 "  other way to do it is to use the PORT command and instruct the server to\n"
 "  connect to the client on the given (as parameters to the PORT command) IP\n"
 "  number and port.\n"
 "\n"
 "  The -P flag to curl supports a few different options. Your machine may have\n"
-, stdout);
- fputs(
 "  several IP-addresses and/or network interfaces and curl allows you to select\n"
 "  which of them to use. Default address can also be used:\n"
 "\n"
 "        curl -P - ftp.download.com\n"
 "\n"
+, stdout);
+ fputs(
 "  Download with PORT but use the IP address of our 'le0' interface (this does\n"
 "  not work on windows):\n"
 "\n"
 "        curl -P le0 ftp.download.com\n"
 "\n"
 "  Download with PORT but use 192.168.0.10 as our IP address to use:\n"
 "\n"
 "        curl -P 192.168.0.10 ftp.download.com\n"
 "\n"
 "NETWORK INTERFACE\n"
 "\n"
-, stdout);
- fputs(
 "  Get a web page from a server using a specified port for the interface:\n"
 "\n"
 "        curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
 "  or\n"
 "\n"
 "        curl --interface 192.168.1.10 http://www.netscape.com/\n"
 "\n"
 "HTTPS\n"
 "\n"
+, stdout);
+ fputs(
 "  Secure HTTP requires SSL libraries to be installed and used when curl is\n"
 "  built. If that is done, curl is capable of retrieving and posting documents\n"
 "  using the HTTPS protocol.\n"
 "\n"
 "  Example:\n"
 "\n"
 "        curl https://www.secure-site.com\n"
 "\n"
-, stdout);
- fputs(
 "  Curl is also capable of using your personal certificates to get/post files\n"
 "  from sites that require valid certificates. The only drawback is that the\n"
 "  certificate needs to be in PEM-format. PEM is a standard and open format to\n"
+, stdout);
+ fputs(
 "  store certificates with, but it is not used by the most commonly used\n"
 "  browsers (Netscape and MSIE both use the so called PKCS#12 format). If you\n"
 "  want curl to use the certificates you use with your (favourite) browser, you\n"
-, stdout);
- fputs(
 "  may need to download/compile a converter that can convert your browser's\n"
 "  formatted certificates to PEM formatted ones. This kind of converter is\n"
 "  included in recent versions of OpenSSL, and for older versions Dr Stephen\n"
+, stdout);
+ fputs(
 "  N. Henson has written a patch for SSLeay that adds this functionality. You\n"
 "  can get his patch (that requires an SSLeay installation) from his site at:\n"
 "  http://www.drh-consultancy.demon.co.uk/\n"
 "\n"
-, stdout);
- fputs(
 "  Example on how to automatically retrieve a document using a certificate with\n"
 "  a personal password:\n"
 "\n"
 "        curl -E /path/to/cert.pem:password https://secure.site.com/\n"
 "\n"
 "  If you neglect to specify the password on the command line, you will be\n"
+, stdout);
+ fputs(
 "  prompted for the correct password before any data can be received.\n"
 "\n"
 "  Many older SSL-servers have problems with SSLv3 or TLS, that newer versions\n"
 "  of OpenSSL etc is using, therefore it is sometimes useful to specify what\n"
-, stdout);
- fputs(
 "  SSL-version curl should use. Use -3, -2 or -1 to specify that exact SSL\n"
 "  version to use (for SSLv3, SSLv2 or TLSv1 respectively):\n"
 "\n"
 "        curl -2 https://secure.site.com/\n"
 "\n"
 "  Otherwise, curl will first attempt to use v3 and then v2.\n"
 "\n"
+, stdout);
+ fputs(
 "  To use OpenSSL to convert your favourite browser's certificate into a PEM\n"
 "  formatted one that curl can use, do something like this (assuming netscape,\n"
 "  but IE is likely to work similarly):\n"
 "\n"
 "    You start with hitting the 'security' menu button in netscape. \n"
 "\n"
-, stdout);
- fputs(
 "    Select 'certificates->yours' and then pick a certificate in the list \n"
 "\n"
 "    Press the 'export' button \n"
 "\n"
 "    enter your PIN code for the certs \n"
 "\n"
 "    select a proper place to save it \n"
 "\n"
+, stdout);
+ fputs(
 "    Run the 'openssl' application to convert the certificate. If you cd to the\n"
 "    openssl installation, you can do it like:\n"
 "\n"
 "     # ./apps/openssl pkcs12 -in [file you saved] -clcerts -out [PEMfile]\n"
 "\n"
 "\n"
 "RESUMING FILE TRANSFERS\n"
 "\n"
 " To continue a file transfer where it was previously aborted, curl supports\n"
-, stdout);
- fputs(
 " resume on http(s) downloads as well as ftp uploads and downloads.\n"
 "\n"
 " Continue downloading a document:\n"
 "\n"
 "        curl -C - -o file ftp://ftp.server.com/path/file\n"
 "\n"
 " Continue uploading a document(*1):\n"
+, stdout);
+ fputs(
 "\n"
 "        curl -C - -T file ftp://ftp.server.com/path/file\n"
 "\n"
 " Continue downloading a document from a web server(*2):\n"
 "\n"
 "        curl -C - -o file http://www.server.com/\n"
 "\n"
 " (*1) = This requires that the ftp server supports the non-standard command\n"
 "        SIZE. If it doesn't, curl will say so.\n"
 "\n"
-, stdout);
- fputs(
 " (*2) = This requires that the web server supports at least HTTP/1.1. If it\n"
 "        doesn't, curl will say so.\n"
 "\n"
 "TIME CONDITIONS\n"
 "\n"
 " HTTP allows a client to specify a time condition for the document it\n"
+, stdout);
+ fputs(
 " requests. It is If-Modified-Since or If-Unmodified-Since. Curl allow you to\n"
 " specify them with the -z/--time-cond flag.\n"
 "\n"
 " For example, you can easily make a download that only gets performed if the\n"
 " remote file is newer than a local copy. It would be made like:\n"
 "\n"
-, stdout);
- fputs(
 "        curl -z local.html http://remote.server.com/remote.html\n"
 "\n"
 " Or you can download a file only if the local file is newer than the remote\n"
 " one. Do this by prepending the date string with a '-', as in:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl -z -local.html http://remote.server.com/remote.html\n"
 "\n"
 " You can specify a \"free text\" date as condition. Tell curl to only download\n"
 " the file if it was updated since yesterday:\n"
 "\n"
 "        curl -z yesterday http://remote.server.com/remote.html\n"
 "\n"
-, stdout);
- fputs(
 " Curl will then accept a wide range of date formats. You always make the date\n"
 " check the other way around by prepending it with a dash '-'.\n"
 "\n"
 "DICT\n"
 "\n"
 "  For fun try\n"
 "\n"
 "        curl dict://dict.org/m:curl\n"
 "        curl dict://dict.org/d:heisenbug:jargon\n"
+, stdout);
+ fputs(
 "        curl dict://dict.org/d:daniel:web1913\n"
 "\n"
 "  Aliases for 'm' are 'match' and 'find', and aliases for 'd' are 'define'\n"
 "  and 'lookup'. For example,\n"
 "\n"
 "        curl dict://dict.org/find:curl\n"
 "\n"
-, stdout);
- fputs(
 "  Commands that break the URL description of the RFC (but not the DICT\n"
 "  protocol) are\n"
 "\n"
 "        curl dict://dict.org/show:db\n"
 "        curl dict://dict.org/show:strat\n"
 "\n"
 "  Authentication is still missing (but this is not required by the RFC)\n"
 "\n"
 "LDAP\n"
 "\n"
+, stdout);
+ fputs(
 "  If you have installed the OpenLDAP library, curl can take advantage of it\n"
 "  and offer ldap:// support.\n"
 "\n"
 "  LDAP is a complex thing and writing an LDAP query is not an easy task. I do\n"
-, stdout);
- fputs(
 "  advice you to dig up the syntax description for that elsewhere. Two places\n"
 "  that might suit you are:\n"
 "\n"
 "  Netscape's \"Netscape Directory SDK 3.0 for C Programmer's Guide Chapter 10:\n"
 "  Working with LDAP URLs\":\n"
 "  http://developer.netscape.com/docs/manuals/dirsdk/csdk30/url.htm\n"
 "\n"
+, stdout);
+ fputs(
 "  RFC 2255, \"The LDAP URL Format\" http://www.rfc-editor.org/rfc/rfc2255.txt\n"
 "\n"
 "  To show you an example, this is now I can get all people from my local LDAP\n"
 "  server that has a certain sub-domain in their email address:\n"
 "\n"
-, stdout);
- fputs(
 "        curl -B \"ldap://ldap.frontec.se/o=frontec??sub?mail=*sth.frontec.se\"\n"
 "\n"
 "  If I want the same info in HTML format, I can get it by not using the -B\n"
 "  (enforce ASCII) flag.\n"
 "\n"
 "ENVIRONMENT VARIABLES\n"
 "\n"
 "  Curl reads and understands the following environment variables:\n"
 "\n"
+, stdout);
+ fputs(
 "        http_proxy, HTTPS_PROXY, FTP_PROXY, GOPHER_PROXY\n"
 "\n"
 "  They should be set for protocol-specific proxies. General proxy should be\n"
 "  set with\n"
 "        \n"
 "        ALL_PROXY\n"
 "\n"
-, stdout);
- fputs(
 "  A comma-separated list of host names that shouldn't go through any proxy is\n"
 "  set in (only an asterisk, '*' matches all hosts)\n"
 "\n"
 "        NO_PROXY\n"
 "\n"
 "  If a tail substring of the domain-path for a host matches one of these\n"
 "  strings, transactions with that node will not be proxied.\n"
 "\n"
 "\n"
+, stdout);
+ fputs(
 "  The usage of the -x/--proxy flag overrides the environment variables.\n"
 "\n"
 "NETRC\n"
 "\n"
 "  Unix introduced the .netrc concept a long time ago. It is a way for a user\n"
-, stdout);
- fputs(
 "  to specify name and password for commonly visited ftp sites in a file so\n"
 "  that you don't have to type them in each time you visit those sites. You\n"
 "  realize this is a big security risk if someone else gets hold of your\n"
 "  passwords, so therefore most unix programs won't read this file unless it is\n"
+, stdout);
+ fputs(
 "  only readable by yourself (curl doesn't care though).\n"
 "\n"
 "  Curl supports .netrc files if told so (using the -n/--netrc and\n"
 "  --netrc-optional options). This is not restricted to only ftp,\n"
-, stdout);
- fputs(
 "  but curl can use it for all protocols where authentication is used.\n"
 "\n"
 "  A very simple .netrc file could look something like:\n"
 "\n"
 "        machine curl.haxx.se login iamdaniel password mysecret\n"
 "\n"
 "CUSTOM OUTPUT\n"
 "\n"
 "  To better allow script programmers to get to know about the progress of\n"
+, stdout);
+ fputs(
 "  curl, the -w/--write-out option was introduced. Using this, you can specify\n"
 "  what information from the previous transfer you want to extract.\n"
 "\n"
-, stdout);
- fputs(
 "  To display the amount of bytes downloaded together with some text and an\n"
 "  ending newline:\n"
 "\n"
 "        curl -w 'We downloaded %{size_download} bytes\\n' www.download.com\n"
 "\n"
 "KERBEROS4 FTP TRANSFER\n"
 "\n"
 "  Curl supports kerberos4 for FTP transfers. You need the kerberos package\n"
 "  installed and used at curl build time for it to be used.\n"
 "\n"
+, stdout);
+ fputs(
 "  First, get the krb-ticket the normal way, like with the kauth tool. Then use\n"
 "  curl in way similar to:\n"
 "\n"
-, stdout);
- fputs(
 "        curl --krb4 private ftp://krb4site.com -u username:fakepwd\n"
 "\n"
 "  There's no use for a password on the -u switch, but a blank one will make\n"
 "  curl ask for one and you already entered the real password to kauth.\n"
 "\n"
 "TELNET\n"
 "\n"
 "  The curl telnet support is basic and very easy to use. Curl passes all data\n"
 "  passed to it on stdin to the remote server. Connect to a remote telnet\n"
+, stdout);
+ fputs(
 "  server using a command line similar to:\n"
 "\n"
 "        curl telnet://remote.server.com\n"
 "\n"
-, stdout);
- fputs(
 "  And enter the data to pass to the server on stdin. The result will be sent\n"
 "  to stdout or to the file you specify with -o.\n"
 "\n"
 "  You might want the -N/--no-buffer option to switch off the buffered output\n"
 "  for slow connections or similar.\n"
 "\n"
 "  Pass options to the telnet protocol negotiation, by using the -t option. To\n"
 "  tell the server we use a vt100 terminal, try something like:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl -tTTYPE=vt100 telnet://remote.server.com\n"
 "\n"
 "  Other interesting options for it -t include:\n"
 "\n"
-, stdout);
- fputs(
 "   - XDISPLOC=<X display> Sets the X display location.\n"
 "\n"
 "   - NEW_ENV=<var,val> Sets an environment variable.\n"
 "\n"
 "  NOTE: the telnet protocol does not specify any way to login with a specified\n"
 "  user and password so curl can't do that automatically. To do that, you need\n"
 "  to track when the login prompt is received and send the username and\n"
 "  password accordingly.\n"
 "\n"
 "PERSISTENT CONNECTIONS\n"
 "\n"
-"  Specifying multiple files on a single command line will make curl transfer\n"
 , stdout);
  fputs(
+"  Specifying multiple files on a single command line will make curl transfer\n"
 "  all of them, one after the other in the specified order.\n"
 "\n"
 "  libcurl will attempt to use persistent connections for the transfers so that\n"
 "  the second transfer to the same host can use the same connection that was\n"
 "  already initiated and was left open in the previous transfer. This greatly\n"
 "  decreases connection time for all but the first transfer and it makes a far\n"
 "  better use of the network.\n"
 "\n"
-"  Note that curl cannot use persistent connections for transfers that are used\n"
 , stdout);
  fputs(
+"  Note that curl cannot use persistent connections for transfers that are used\n"
 "  in subsequence curl invokes. Try to stuff as many URLs as possible on the\n"
 "  same command line if they are using the same host, as that'll make the\n"
 "  transfers faster. If you use a http proxy for file transfers, practically\n"
 "  all transfers will be persistent.\n"
 "\n"
 "MAILING LISTS\n"
 "\n"
 "  For your convenience, we have several open mailing lists to discuss curl,\n"
 "  its development and things relevant to this. Get all info at\n"
+, stdout);
+ fputs(
 "  http://curl.haxx.se/mail/. Some of the lists available are:\n"
 "\n"
 "  curl-users\n"
 "\n"
-, stdout);
- fputs(
 "    Users of the command line tool. How to use it, what doesn't work, new\n"
 "    features, related tools, questions, news, installations, compilations,\n"
 "    running, porting etc.\n"
 "\n"
 "  curl-library\n"
 "\n"
 "    Developers using or developing libcurl. Bugs, extensions, improvements.\n"
 "\n"
 "  curl-announce\n"
 "\n"
 "    Low-traffic. Only receives announcements of new public versions. At worst,\n"
+, stdout);
+ fputs(
 "    that makes something like one or two mails per month, but usually only one\n"
 "    mail every second month.\n"
 "\n"
 "  curl-and-php\n"
 "\n"
-, stdout);
- fputs(
 "    Using the curl functions in PHP. Everything curl with a PHP angle. Or PHP\n"
 "    with a curl angle.\n"
 "\n"
 "  curl-and-python\n"
 "\n"
 "    Python hackers using curl with or without the python binding pycurl.\n"
