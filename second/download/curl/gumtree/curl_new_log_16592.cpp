puts(
"  ';type=<mime type>' to the file name. You can also post contents of several\n"
"  files in one field. So that the field name 'coolfiles' can be sent three\n"
"  files with different content types in a manner similar to:\n"
"\n"
"        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
"        http://www.post.com/postit.cgi\n"
"\n"
"  If content-type is not specified, curl will try to guess from the extension\n"
"  (it only knows a few), or use the previously specified type (from an earlier\n"
);