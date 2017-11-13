fputs(
"  path the \"cookie\" should be used for (by specifying \"path=value\"), when the\n"
"  cookie should expire (\"expire=DATE\"), for what domain to use it\n"
"  (\"domain=NAME\") and if it should be used on secure connections only\n"
"  (\"secure\").\n"
"\n"
"  If you've received a page from a server that contains a header like:\n"
"        Set-Cookie: sessionid=boo123; path=\"/foo\";\n"
"\n"
"  it means the server wants that first pair passed on when we get anything in\n"
"  a path beginning with \"/foo\".\n"
"\n"
, stdout);