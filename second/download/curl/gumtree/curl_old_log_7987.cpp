fputs(
"        curl -d \"user=foobar&pass=12345&id=blablabla&ding=submit\"  (continues)\n"
"          http://www.formpost.com/getthis/post.cgi\n"
"\n"
"\n"
"  While -d uses the application/x-www-form-urlencoded mime-type, generally\n"
"  understood by CGI's and similar, curl also supports the more capable\n"
"  multipart/form-data type. This latter type supports things like file upload.\n"
"\n"
"  -F accepts parameters like -F \"name=contents\". If you want the contents to\n"
, stdout);