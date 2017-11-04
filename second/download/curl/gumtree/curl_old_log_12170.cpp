fputs(
"  be read from a file, use <@filename> as contents. When specifying a file,\n"
"  you can also specify the file content type by appending ';type=<mime type>'\n"
"  to the file name. You can also post the contents of several files in one\n"
"  field.  For example, the field name 'coolfiles' is used to send three files,\n"
"  with different content types using the following syntax:\n"
"\n"
"        curl -F \"coolfiles=@fil1.gif;type=image/gif,fil2.txt,fil3.html\" \\\n"
"        http://www.post.com/postit.cgi\n"
"\n"
, stdout);