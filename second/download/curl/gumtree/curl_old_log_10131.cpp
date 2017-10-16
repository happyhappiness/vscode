fputs(
"        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
"        http://www.post.com/postit.cgi\n"
"\n"
"  If the content-type is not specified, curl will try to guess from the file\n"
"  extension (it only knows a few), or use the previously specified type (from\n"
"  an earlier file if several files are specified in a list) or else it will\n"
"  use the default type 'application/octet-stream'.\n"
"\n"
"  Emulate a fill-in form with -F. Let's say you fill in three fields in a\n"
, stdout);