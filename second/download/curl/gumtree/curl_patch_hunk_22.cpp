 "  a path beginning with \"/foo\".\n"
 "\n"
 "  Example, get a page that wants my name passed in a cookie:\n"
 "\n"
 "        curl -b \"name=Daniel\" www.sillypage.com\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  Curl also has the ability to use previously received cookies in following\n"
 "  sessions. If you get cookies from a server and store them in a file in a\n"
 "  manner similar to:\n"
 "\n"
 "        curl --dump-header headers www.example.com\n"
 "\n"
 "  ... you can then in a second connect to that (or another) site, use the\n"
 "  cookies from the 'headers' file like:\n"
 "\n"
 "        curl -b headers www.example.com\n"
 "\n"
 "  While saving headers to a file is a working way to store cookies, it is\n"
-);
- puts(
+, stdout);
+ fputs(
 "  however error-prone and not the prefered way to do this. Instead, make curl\n"
 "  save the incoming cookies using the well-known netscape cookie format like\n"
 "  this:\n"
 "\n"
 "        curl -c cookies.txt www.example.com\n"
 "\n"
 "  Note that by specifying -b you enable the \"cookie awareness\" and with -L\n"
 "  you can make curl follow a location: (which often is used in combination\n"
 "  with cookies). So that if a site sends cookies and a location, you can\n"
 "  use a non-existing file to trigger the cookie awareness like:\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "        curl -L -b empty.txt www.example.com\n"
 "\n"
 "  The file to read cookies from must be formatted using plain HTTP headers OR\n"
 "  as netscape's cookie file. Curl will determine what kind it is based on the\n"
 "  file contents.  In the above command, curl will parse the header and store\n"
 "  the cookies received from www.example.com.  curl will send to the server the\n"
 "  stored cookies which match the request as it follows the location.  The\n"
 "  file \"empty.txt\" may be a non-existant file.\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  Alas, to both read and write cookies from a netscape cookie file, you can\n"
 "  set both -b and -c to use the same file:\n"
 "\n"
 "        curl -b cookies.txt -c cookies.txt www.example.com\n"
 "\n"
 "PROGRESS METER\n"
 "\n"
 "  The progress meter exists to show a user that something actually is\n"
 "  happening. The different fields in the output have the following meaning:\n"
 "\n"
 "  % Total    % Received % Xferd  Average Speed          Time             Curr.\n"
-);
- puts(
+, stdout);
+ fputs(
 "                                 Dload  Upload Total    Current  Left    Speed\n"
 "  0  151M    0 38608    0     0   9406      0  4:41:43  0:00:04  4:41:39  9287\n"
 "\n"
 "  From left-to-right:\n"
 "   %             - percentage completed of the whole transfer\n"
 "   Total         - total size of the whole expected transfer\n"
 "   %             - percentage completed of the download\n"
 "   Received      - currently downloaded amount of bytes\n"
 "   %             - percentage completed of the upload\n"
-);
- puts(
+, stdout);
+ fputs(
 "   Xferd         - currently uploaded amount of bytes\n"
 "   Average Speed\n"
 "   Dload         - the average transfer speed of the download\n"
 "   Average Speed\n"
 "   Upload        - the average transfer speed of the upload\n"
 "   Time Total    - expected time to complete the operation\n"
 "   Time Current  - time passed since the invoke\n"
 "   Time Left     - expected time left to completetion\n"
 "   Curr.Speed    - the average transfer speed the last 5 seconds (the first\n"
-);
- puts(
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
 "  to let the transfer keep going. By using the switch -y and -Y you\n"
 "  can make curl abort transfers if the transfer speed is below the specified\n"
 "  lowest limit for a specified time.\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  To have curl abort the download if the speed is slower than 3000 bytes per\n"
 "  second for 1 minute, run:\n"
 "\n"
 "        curl -Y 3000 -y 60 www.far-away-site.com\n"
 "\n"
 "  This can very well be used in combination with the overall time limit, so\n"
 "  that the above operatioin must be completed in whole within 30 minutes:\n"
 "\n"
 "        curl -m 1800 -Y 3000 -y 60 www.far-away-site.com\n"
 "\n"
 "  Forcing curl not to transfer data faster than a given rate is also possible,\n"
-);
- puts(
+, stdout);
+ fputs(
 "  which might be useful if you're using a limited bandwidth connection and you\n"
 "  don't want your transfer to use all of it (sometimes referred to as\n"
 "  \"bandwith throttle\").\n"
 "\n"
 "  Make curl transfer data no faster than 10 kilobytes per second:\n"
 "\n"
