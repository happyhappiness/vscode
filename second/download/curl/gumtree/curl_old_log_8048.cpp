fputs(
"              To  be  CGI-compliant,  the <data> part should begin with a name\n"
"              followed by a separator and a content specification. The  <data>\n"
"              part can be passed to curl using one of the following syntaxes:\n"
"\n"
"              content\n"
"                     This  will make curl URL-encode the content and pass that\n"
"                     on. Just be careful so that the content  doesn't  contain\n"
"                     any  =  or  @  symbols, as that will then make the syntax\n"
, stdout);