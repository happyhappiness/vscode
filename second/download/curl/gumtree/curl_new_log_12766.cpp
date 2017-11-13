fputs(
"              that @ makes a file get attached in the post as a  file  upload,\n"
"              while  the  <  makes  a text field and just get the contents for\n"
"              that text field from a file.\n"
"\n"
"              Example: to send an image to a server, where  'profile'  is  the\n"
"              name of the form-field to which portrait.jpg will be the input:\n"
"\n"
"              curl -F profile=@portrait.jpg https://example.com/upload.cgi\n"
"\n"
, stdout);