 "        curl -r 0-99 ftp://www.get.this/README  \n"
 "\n"
 "UPLOADING\n"
 "\n"
 " FTP\n"
 "\n"
-);
- puts(
 "  Upload all data on stdin to a specified ftp site:\n"
 "\n"
 "        curl -t ftp://ftp.upload.com/myfile\n"
 "\n"
+);
+ puts(
 "  Upload data from a specified file, login with user and password:\n"
 "\n"
 "        curl -T uploadfile -u user:passwd ftp://ftp.upload.com/myfile\n"
 "\n"
 "  Upload a local file to the remote site, and use the local file name remote\n"
 "  too:\n"
 " \n"
 "        curl -T uploadfile -u user:passwd ftp://ftp.upload.com/\n"
 "\n"
 "  Upload a local file to get appended to the remote file using ftp:\n"
 "\n"
-);
- puts(
 "        curl -T localfile -a ftp://ftp.upload.com/remotefile\n"
 "\n"
 "  Curl also supports ftp upload through a proxy, but only if the proxy is\n"
+);
+ puts(
 "  configured to allow that kind of tunneling. If it does, you can run curl in\n"
 "  a fashion similar to:\n"
 "\n"
 "        curl --proxytunnel -x proxy:port -T localfile ftp.upload.com\n"
 "\n"
 " HTTP\n"
 "\n"
 "  Upload all data on stdin to a specified http site:\n"
 "\n"
 "        curl -t http://www.upload.com/myfile\n"
 "\n"
 "  Note that the http server must've been configured to accept PUT before this\n"
-);
- puts(
 "  can be done successfully.\n"
 "\n"
 "  For other ways to do http data upload, see the POST section below.\n"
 "\n"
 "VERBOSE / DEBUG\n"
 "\n"
+);
+ puts(
 "  If curl fails where it isn't supposed to, if the servers don't let you\n"
 "  in, if you can't understand the responses: use the -v flag to get VERBOSE\n"
 "  fetching. Curl will output lots of info and all data it sends and\n"
 "  receives in order to let the user see all client-server interaction.\n"
 "\n"
 "        curl -v ftp://ftp.upload.com/\n"
 "\n"
 "DETAILED INFORMATION\n"
 "\n"
+"  Different protocols provide different ways of getting detailed information\n"
 );
  puts(
-"  Different protocols provide different ways of getting detailed information\n"
 "  about specific files/documents. To get curl to show detailed information\n"
 "  about a single file, you should use -I/--head option. It displays all\n"
 "  available info on a single file for HTTP and FTP. The HTTP information is a\n"
 "  lot more extensive.\n"
 "\n"
 "  For HTTP, you can get the header information (the same as -I would show)\n"
 "  shown before the data by using -i/--include. Curl understands the\n"
+"  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
 );
  puts(
-"  -D/--dump-header option when getting files from both FTP and HTTP, and it\n"
 "  will then store the headers in the specified file.\n"
 "\n"
-"  Store the HTTP headers in a separate file:\n"
+"  Store the HTTP headers in a separate file (headers.txt in the example):\n"
 "\n"
 "        curl --dump-header headers.txt curl.haxx.se\n"
 "\n"
 "  Note that headers stored in a separate file can be very useful at a later\n"
 "  time if you want curl to use cookies sent by the server. More about that in\n"
 "  the cookies section.\n"
 "\n"
 "POST (HTTP)\n"
 "\n"
 "  It's easy to post data using curl. This is done using the -d <data>\n"
-);
- puts(
 "  option.  The post data must be urlencoded.\n"
 "\n"
+);
+ puts(
 "  Post a simple \"name\" and \"phone\" guestbook.\n"
 "\n"
 "        curl -d \"name=Rafael%20Sagula&phone=3320780\" \\\n"
 "                http://www.where.com/guest.cgi\n"
 "\n"
 "  How to post a form with curl, lesson #1:\n"
 "\n"
 "  Dig out all the <input> tags in the form that you want to fill in. (There's\n"
 "  a perl program called formfind.pl on the curl site that helps with this).\n"
 "\n"
 "  If there's a \"normal\" post, you use -d to post. -d takes a full \"post\n"
-);
- puts(
 "  string\", which is in the format\n"
 "\n"
+);
+ puts(
 "        <variable1>=<data1>&<variable2>=<data2>&...\n"
 "\n"
 "  The 'variable' names are the names set with \"name=\" in the <input> tags, and\n"
 "  the data is the contents you want to fill in for the inputs. The data *must*\n"
 "  be properly URL encoded. That means you replace space with + and that you\n"
 "  write weird letters with %XX where XX is the hexadecimal representation of\n"
