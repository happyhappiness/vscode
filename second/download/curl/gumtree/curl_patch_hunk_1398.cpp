 "   Curl features no password support for gopher.\n"
 "\n"
 "PROXY\n"
 "\n"
 " Get an ftp file using a proxy named my-proxy that uses port 888:\n"
 "\n"
+);
+ puts(
 "        curl -x my-proxy:888 ftp://ftp.leachsite.com/README\n"
 "\n"
 " Get a file from a HTTP server that requires user and password, using the\n"
 " same proxy as above:\n"
 "\n"
-);
- puts(
 "        curl -u user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
 " Some proxies require special authentication. Specify by using -U as above:\n"
 "\n"
 "        curl -U user:passwd -x my-proxy:888 http://www.get.this/\n"
 "\n"
 " See also the environment variables Curl support that offer further proxy\n"
 " control.\n"
 "\n"
 "RANGES\n"
 "\n"
+);
+ puts(
 "  With HTTP 1.1 byte-ranges were introduced. Using this, a client can request\n"
 "  to get only one or more subparts of a specified document. Curl supports\n"
 "  this with the -r flag.\n"
 "\n"
-);
- puts(
 "  Get the first 100 bytes of a document:\n"
 "\n"
 "        curl -r 0-99 http://www.get.this/\n"
 "\n"
 "  Get the last 500 bytes of a document:\n"
 "\n"
 "        curl -r -500 http://www.get.this/\n"
 "\n"
 "  Curl also supports simple ranges for FTP files as well. Then you can only\n"
 "  specify start and stop position.\n"
 "\n"
+);
+ puts(
 "  Get the first 100 bytes of a document using FTP:\n"
 "\n"
 "        curl -r 0-99 ftp://www.get.this/README  \n"
 "\n"
 "UPLOADING\n"
 "\n"
 " FTP\n"
 "\n"
 "  Upload all data on stdin to a specified ftp site:\n"
 "\n"
 "        curl -t ftp://ftp.upload.com/myfile\n"
 "\n"
-);
- puts(
 "  Upload data from a specified file, login with user and password:\n"
 "\n"
 "        curl -T uploadfile -u user:passwd ftp://ftp.upload.com/myfile\n"
 "\n"
 "  Upload a local file to the remote site, and use the local file name remote\n"
 "  too:\n"
 " \n"
+);
+ puts(
 "        curl -T uploadfile -u user:passwd ftp://ftp.upload.com/\n"
 "\n"
 "  Upload a local file to get appended to the remote file using ftp:\n"
 "\n"
 "        curl -T localfile -a ftp://ftp.upload.com/remotefile\n"
 "\n"
 "  Curl also supports ftp upload through a proxy, but only if the proxy is\n"
-);
- puts(
 "  configured to allow that kind of tunneling. If it does, you can run curl in\n"
 "  a fashion similar to:\n"
 "\n"
 "        curl --proxytunnel -x proxy:port -T localfile ftp.upload.com\n"
 "\n"
 " HTTP\n"
 "\n"
+);
+ puts(
 "  Upload all data on stdin to a specified http site:\n"
 "\n"
 "        curl -t http://www.upload.com/myfile\n"
 "\n"
 "  Note that the http server must've been configured to accept PUT before this\n"
 "  can be done successfully.\n"
 "\n"
 "  For other ways to do http data upload, see the POST section below.\n"
 "\n"
 "VERBOSE / DEBUG\n"
 "\n"
-);
- puts(
 "  If curl fails where it isn't supposed to, if the servers don't let you\n"
 "  in, if you can't understand the responses: use the -v flag to get VERBOSE\n"
+);
+ puts(
 "  fetching. Curl will output lots of info and all data it sends and\n"
 "  receives in order to let the user see all client-server interaction.\n"
 "\n"
 "        curl -v ftp://ftp.upload.com/\n"
 "\n"
 "DETAILED INFORMATION\n"
 "\n"
 "  Different protocols provide different ways of getting detailed information\n"
-);
- puts(
 "  about specific files/documents. To get curl to show detailed information\n"
 "  about a single file, you should use -I/--head option. It displays all\n"
+);
+ puts(
 "  available info on a single file for HTTP and FTP. The HTTP information is a\n"
 "  lot more extensive.\n"
 "\n"
 "  For HTTP, you can get the header information (the same as -I would show)\n"
 "  shown before the data by using -i/--include. Curl understands the\n"
 "  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
-);
- puts(
 "  will then store the headers in the specified file.\n"
 "\n"
 "  Store the HTTP headers in a separate file (headers.txt in the example):\n"
 "\n"
+);
+ puts(
 "        curl --dump-header headers.txt curl.haxx.se\n"
 "\n"
 "  Note that headers stored in a separate file can be very useful at a later\n"
 "  time if you want curl to use cookies sent by the server. More about that in\n"
 "  the cookies section.\n"
 "\n"
 "POST (HTTP)\n"
 "\n"
 "  It's easy to post data using curl. This is done using the -d <data>\n"
 "  option.  The post data must be urlencoded.\n"
 "\n"
-);
- puts(
 "  Post a simple \"name\" and \"phone\" guestbook.\n"
 "\n"
 "        curl -d \"name=Rafael%20Sagula&phone=3320780\" \\\n"
+);
+ puts(
 "                http://www.where.com/guest.cgi\n"
 "\n"
 "  How to post a form with curl, lesson #1:\n"
 "\n"
 "  Dig out all the <input> tags in the form that you want to fill in. (There's\n"
 "  a perl program called formfind.pl on the curl site that helps with this).\n"
 "\n"
 "  If there's a \"normal\" post, you use -d to post. -d takes a full \"post\n"
 "  string\", which is in the format\n"
 "\n"
-);
- puts(
 "        <variable1>=<data1>&<variable2>=<data2>&...\n"
 "\n"
 "  The 'variable' names are the names set with \"name=\" in the <input> tags, and\n"
+);
+ puts(
 "  the data is the contents you want to fill in for the inputs. The data *must*\n"
 "  be properly URL encoded. That means you replace space with + and that you\n"
 "  write weird letters with %XX where XX is the hexadecimal representation of\n"
 "  the letter's ASCII code.\n"
 "\n"
 "  Example:\n"
 "\n"
 "  (page located at http://www.formpost.com/getthis/\n"
 "\n"
-);
- puts(
 "        <form action=\"post.cgi\" method=\"post\">\n"
 "        <input name=user size=10>\n"
 "        <input name=pass type=password size=10>\n"
+);
+ puts(
 "        <input name=id type=hidden value=\"blablabla\">\n"
 "        <input name=ding value=\"submit\">\n"
 "        </form>\n"
 "\n"
 "  We want to enter user 'foobar' with password '12345'.\n"
 "\n"
 "  To post to this, you enter a curl command line like:\n"
 "\n"
 "        curl -d \"user=foobar&pass=12345&id=blablabla&dig=submit\"  (continues)\n"
 "          http://www.formpost.com/getthis/post.cgi\n"
 "\n"
 "\n"
+"  While -d uses the application/x-www-form-urlencoded mime-type, generally\n"
 );
  puts(
-"  While -d uses the application/x-www-form-urlencoded mime-type, generally\n"
 "  understood by CGI's and similar, curl also supports the more capable\n"
 "  multipart/form-data type. This latter type supports things like file upload.\n"
 "\n"
 "  -F accepts parameters like -F \"name=contents\". If you want the contents to\n"
 "  be read from a file, use <@filename> as contents. When specifying a file,\n"
 "  you can also specify the file content type by appending ';type=<mime type>'\n"
+"  to the file name. You can also post the contents of several files in one field.\n"
 );
  puts(
-"  to the file name. You can also post the contents of several files in one field.\n"
 "  For example, the field name 'coolfiles' is used to send three  files, with\n"
 "  different content types using the following syntax:\n"
 "\n"
 "        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
 "        http://www.post.com/postit.cgi\n"
 "\n"
 "  If the content-type is not specified, curl will try to guess from the file\n"
 "  extension  (it only knows a few), or use the previously specified type\n"
+"  (from an earlier file if several files are specified in a list) or else it\n"
 );
  puts(
-"  (from an earlier file if several files are specified in a list) or else it\n"
 "  will  using the default type 'text/plain'.\n"
 "\n"
 "  Emulate a fill-in form with -F. Let's say you fill in three fields in a\n"
 "  form. One field is a file name which to post, one field is your name and one\n"
 "  field is a file description. We want to post the file we have written named\n"
 "  \"cooltext.txt\". To let curl do the posting of this data instead of your\n"
+"  favourite browser, you have to read the HTML source of the form page and find\n"
 );
  puts(
-"  favourite browser, you have to read the HTML source of the form page and find\n"
 "  the names of the input fields. In our example, the input field names are\n"
 "  'file', 'yourname' and 'filedescription'.\n"
 "\n"
 "        curl -F \"file=@cooltext.txt\" -F \"yourname=Daniel\" \\\n"
 "             -F \"filedescription=Cool text file with cool text inside\" \\\n"
 "             http://www.post.com/postit.cgi\n"
 "\n"
 "  To send two files in one post you can do it in two ways:\n"
 "\n"
-);
- puts(
 "  1. Send multiple files in a single \"field\" with a single field name:\n"
 " \n"
 "        curl -F \"pictures=@dog.gif,cat.gif\" \n"
 " \n"
+);
+ puts(
 "  2. Send two fields with two field names: \n"
 "\n"
 "        curl -F \"docpicture=@dog.gif\" -F \"catpicture=@cat.gif\" \n"
 "\n"
 "REFERRER\n"
 "\n"
 "  A HTTP request has the option to include information about which address\n"
 "  that referred to actual page.  Curl allows you to specify the\n"
 "  referrer to be used on the command line. It is especially useful to\n"
-);
- puts(
 "  fool or trick stupid servers or CGI scripts that rely on that information\n"
 "  being available or contain certain data.\n"
 "\n"
+);
+ puts(
 "        curl -e www.coolsite.com http://www.showme.com/\n"
 "\n"
 "  NOTE: The referer field is defined in the HTTP spec to be a full URL.\n"
 "\n"
 "USER AGENT\n"
 "\n"
 "  A HTTP request has the option to include information about the browser\n"
 "  that generated the request. Curl allows it to be specified on the command\n"
 "  line. It is especially useful to fool or trick stupid servers or CGI\n"
-);
- puts(
 "  scripts that only accept certain browsers.\n"
 "\n"
 "  Example:\n"
 "\n"
 "  curl -A 'Mozilla/3.0 (Win95; I)' http://www.nationsbank.com/\n"
 "\n"
+);
+ puts(
 "  Other common strings:\n"
 "    'Mozilla/3.0 (Win95; I)'     Netscape Version 3 for Windows 95\n"
 "    'Mozilla/3.04 (Win95; U)'    Netscape Version 3 for Windows 95\n"
 "    'Mozilla/2.02 (OS/2; U)'     Netscape Version 2 for OS/2\n"
 "    'Mozilla/4.04 [en] (X11; U; AIX 4.2; Nav)'           NS for AIX\n"
 "    'Mozilla/4.05 [en] (X11; U; Linux 2.0.32 i586)'      NS for Linux\n"
 "\n"
-);
- puts(
 "  Note that Internet Explorer tries hard to be compatible in every way:\n"
 "    'Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)'    MSIE for W95\n"
+);
+ puts(
 "\n"
 "  Mozilla is not the only possible User-Agent name:\n"
 "    'Konqueror/1.0'             KDE File Manager desktop client\n"
 "    'Lynx/2.7.1 libwww-FM/2.14' Lynx command line browser\n"
 "\n"
 "COOKIES\n"
 "\n"
 "  Cookies are generally used by web servers to keep state information at the\n"
 "  client's side. The server sets cookies by sending a response line in the\n"
-);
- puts(
 "  headers that looks like 'Set-Cookie: <data>' where the data part then\n"
 "  typically contains a set of NAME=VALUE pairs (separated by semicolons ';'\n"
+);
+ puts(
 "  like \"NAME1=VALUE1; NAME2=VALUE2;\"). The server can also specify for what\n"
 "  path the \"cookie\" should be used for (by specifying \"path=value\"), when the\n"
 "  cookie should expire (\"expire=DATE\"), for what domain to use it\n"
 "  (\"domain=NAME\") and if it should be used on secure connections only\n"
 "  (\"secure\").\n"
 "\n"
-);
- puts(
 "  If you've received a page from a server that contains a header like:\n"
 "        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
 "\n"
+);
+ puts(
 "  it means the server wants that first pair passed on when we get anything in\n"
 "  a path beginning with \"/foo\".\n"
 "\n"
 "  Example, get a page that wants my name passed in a cookie:\n"
 "\n"
 "        curl -b \"name=Daniel\" www.sillypage.com\n"
 "\n"
 "  Curl also has the ability to use previously received cookies in following\n"
 "  sessions. If you get cookies from a server and store them in a file in a\n"
-);
- puts(
 "  manner similar to:\n"
 "\n"
 "        curl --dump-header headers www.example.com\n"
 "\n"
+);
+ puts(
 "  ... you can then in a second connect to that (or another) site, use the\n"
 "  cookies from the 'headers' file like:\n"
 "\n"
 "        curl -b headers www.example.com\n"
 "\n"
 "  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
 "  you can make curl follow a location: (which often is used in combination\n"
 "  with cookies). So that if a site sends cookies and a location, you can\n"
-);
- puts(
 "  use a non-existing file to trigger the cookie awareness like:\n"
 "\n"
 "        curl -L -b empty.txt www.example.com\n"
 "\n"
+);
+ puts(
 "  The file to read cookies from must be formatted using plain HTTP headers OR\n"
 "  as netscape's cookie file. Curl will determine what kind it is based on the\n"
 "  file contents.  In the above command, curl will parse the header and store\n"
 "  the cookies received from www.example.com.  curl will send to the server the\n"
 "  stored cookies which match the request as it follows the location.  The\n"
-);
- puts(
 "  file \"empty.txt\" may be a non-existant file.\n"
 "  \n"
 "\n"
 "PROGRESS METER\n"
 "\n"
+);
+ puts(
 "  The progress meter exists to show a user that something actually is\n"
 "  happening. The different fields in the output have the following meaning:\n"
 "\n"
 "  % Total    % Received % Xferd  Average Speed          Time             Curr.\n"
 "                                 Dload  Upload Total    Current  Left    Speed\n"
 "  0  151M    0 38608    0     0   9406      0  4:41:43  0:00:04  4:41:39  9287\n"
 "\n"
 "  From left-to-right:\n"
+"   %             - percentage completed of the whole transfer\n"
 );
  puts(
-"   %             - percentage completed of the whole transfer\n"
 "   Total         - total size of the whole expected transfer\n"
 "   %             - percentage completed of the download\n"
 "   Received      - currently downloaded amount of bytes\n"
 "   %             - percentage completed of the upload\n"
 "   Xferd         - currently uploaded amount of bytes\n"
 "   Average Speed\n"
 "   Dload         - the average transfer speed of the download\n"
 "   Average Speed\n"
 "   Upload        - the average transfer speed of the upload\n"
+"   Time Total    - expected time to complete the operation\n"
 );
  puts(
-"   Time Total    - expected time to complete the operation\n"
 "   Time Current  - time passed since the invoke\n"
 "   Time Left     - expected time left to completetion\n"
 "   Curr.Speed    - the average transfer speed the last 5 seconds (the first\n"
 "                   5 seconds of a transfer is based on less time of course.)\n"
 "\n"
 "  The -# option will display a totally different progress bar that doesn't\n"
 "  need much explanation!\n"
 "\n"
 "SPEED LIMIT\n"
 "\n"
+"  Curl allows the user to set the transfer speed conditions that must be met\n"
 );
  puts(
-"  Curl allows the user to set the transfer speed conditions that must be met\n"
 "  to let the transfer keep going. By using the switch -y and -Y you\n"
 "  can make curl abort transfers if the transfer speed is below the specified\n"
 "  lowest limit for a specified time.\n"
 "\n"
 "  To have curl abort the download if the speed is slower than 3000 bytes per\n"
 "  second for 1 minute, run:\n"
 "\n"
 "        curl -y 3000 -Y 60 www.far-away-site.com\n"
 "\n"
 "  This can very well be used in combination with the overall time limit, so\n"
-);
- puts(
 "  that the above operatioin must be completed in whole within 30 minutes:\n"
 "\n"
+);
+ puts(
 "        curl -m 1800 -y 3000 -Y 60 www.far-away-site.com\n"
 "\n"
 "CONFIG FILE\n"
 "\n"
 "  Curl automatically tries to read the .curlrc file (or _curlrc file on win32\n"
 "  systems) from the user's home dir on startup.\n"
 "\n"
 "  The config file could be made up with normal command line switches, but you\n"
 "  can also specify the long options without the dashes to make it more\n"
 "  readable. You can separate the options and the parameter with spaces, or\n"
+"  with = or :. Comments can be used within the file. If the first letter on a\n"
 );
  puts(
-"  with = or :. Comments can be used within the file. If the first letter on a\n"
 "  line is a '#'-letter the rest of the line is treated as a comment.\n"
 "\n"
 "  If you want the parameter to contain spaces, you must inclose the entire\n"
 "  parameter within double quotes (\"). Within those quotes, you specify a\n"
 "  quote as \\\".\n"
 "\n"
 "  NOTE: You must specify options and their arguments on the same line.\n"
 "\n"
 "  Example, set default time out and proxy in a config file:\n"
 "\n"
 "        # We want a 30 minute timeout:\n"
 "        -m 1800\n"
+"        # ... and we use a proxy for all accesses:\n"
 );
  puts(
-"        # ... and we use a proxy for all accesses:\n"
 "        proxy = proxy.our.domain.com:8080\n"
 "\n"
 "  White spaces ARE significant at the end of lines, but all white spaces\n"
 "  leading up to the first characters of each line are ignored.\n"
 "\n"
 "  Prevent curl from reading the default file by using -q as the first command\n"
