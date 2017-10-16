"  favourite browser, you have to check out the HTML of the form page to get to\n"
"  know the names of the input fields. In our example, the input field names are\n"
"  'file', 'yourname' and 'filedescription'.\n"
"\n"
"        curl -F \"file=@cooltext.txt\" -F \"yourname=Daniel\" \\\n"
"             -F \"filedescription=Cool text file with cool text inside\" \\\n"
);
 puts(
"             http://www.post.com/postit.cgi\n"
"\n"
"  So, to send two files in one post you can do it in two ways:\n"
"\n"
"  1. Send multiple files in a single \"field\" with a single field name:\n"
" \n"
