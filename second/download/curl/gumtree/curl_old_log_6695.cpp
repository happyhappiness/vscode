fputs(
"              name=content\n"
"                     This  will make curl URL-encode the content part and pass\n"
"                     that on. Note that the name part is expected to  be  URL-\n"
"                     encoded already.\n"
"\n"
"              @filename\n"
"                     This  will  make  curl  load  data  from  the  given file\n"
"                     (including any newlines), URL-encode that data  and  pass\n"
"                     it on in the POST.\n"
"\n"
"              name@filename\n"
, stdout);