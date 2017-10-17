fputs(
"              multiple files to a single URL by using the  same  URL  globbing\n"
"              style supported in the URL, like this:\n"
"\n"
"              curl -T \"{file1,file2}\" http://www.uploadtothissite.com\n"
"\n"
"              or even\n"
"\n"
"              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
"\n"
"       --trace <file>\n"
"              Enables  a  full  trace  dump of all incoming and outgoing data,\n"
"              including descriptive information, to the given output file. Use\n"
, stdout);