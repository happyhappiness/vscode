puts(
"  favourite browser, you have to read the HTML source of the form page and find\n"
"  the names of the input fields. In our example, the input field names are\n"
"  'file', 'yourname' and 'filedescription'.\n"
"\n"
"        curl -F \"file=@cooltext.txt\" -F \"yourname=Daniel\" \\\n"
"             -F \"filedescription=Cool text file with cool text inside\" \\\n"
"             http://www.post.com/postit.cgi\n"
"\n"
"  To send two files in one post you can do it in two ways:\n"
"\n"
);