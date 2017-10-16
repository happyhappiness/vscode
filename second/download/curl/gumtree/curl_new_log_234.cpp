puts(
"  form. One field is a file name which to post, one field is your name and one\n"
"  field is a file description. We want to post the file we have written named\n"
"  \"cooltext.txt\". To let curl do the posting of this data instead of your\n"
"  favourite browser, you have to read the HTML source of the form page and\n"
"  find the names of the input fields. In our example, the input field names\n"
"  are 'file', 'yourname' and 'filedescription'.\n"
"\n"
"        curl -F \"file=@cooltext.txt\" -F \"yourname=Daniel\" \\\n"
);