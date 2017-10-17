puts(
"  to the file name. You can also post the contents of several files in one field.\n"
"  For example, the field name 'coolfiles' is used to send three  files, with\n"
"  different content types using the following syntax:\n"
"\n"
"        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
"        http://www.post.com/postit.cgi\n"
"\n"
"  If the content-type is not specified, curl will try to guess from the file\n"
"  extension  (it only knows a few), or use the previously specified type\n"
);