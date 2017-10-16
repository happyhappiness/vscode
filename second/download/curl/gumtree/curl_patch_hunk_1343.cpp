 "  time if you want curl to use cookies sent by the server. More about that in\n"
 "  the cookies section.\n"
 "\n"
 "POST (HTTP)\n"
 "\n"
 "  It's easy to post data using curl. This is done using the -d <data>\n"
+);
+ puts(
 "  option.  The post data must be urlencoded.\n"
 "\n"
 "  Post a simple \"name\" and \"phone\" guestbook.\n"
 "\n"
 "        curl -d \"name=Rafael%20Sagula&phone=3320780\" \\\n"
 "                http://www.where.com/guest.cgi\n"
