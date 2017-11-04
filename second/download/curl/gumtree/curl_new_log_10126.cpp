fputs(
"  If you've received a page from a server that contains a header like:\n"
"        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
"\n"
"  it means the server wants that first pair passed on when we get anything in\n"
"  a path beginning with \"/foo\".\n"
"\n"
"  Example, get a page that wants my name passed in a cookie:\n"
"\n"
"        curl -b \"name=Daniel\" www.sillypage.com\n"
"\n"
"  Curl also has the ability to use previously received cookies in following\n"
"  sessions. If you get cookies from a server and store them in a file in a\n"
, stdout);