 "  Example, send the header \"X-you-and-me: yes\" to the server when getting a\n"
 "  page:\n"
 "\n"
 "        curl -H \"X-you-and-me: yes\" www.love.com\n"
 "\n"
 "  This can also be useful in case you want curl to send a different text in a\n"
-);
- puts(
+, stdout);
+ fputs(
 "  header than it normally does. The -H header you specify then replaces the\n"
 "  header curl would normally send. If you replace an internal header with an\n"
 "  empty one, you prevent that header from being sent. To prevent the Host:\n"
 "  header from being used:\n"
 "\n"
 "        curl -H \"Host:\" www.server.com\n"
