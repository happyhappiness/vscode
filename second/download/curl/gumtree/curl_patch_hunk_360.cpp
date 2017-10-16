 "\n"
 "              content\n"
 "                     This  will make curl URL-encode the content and pass that\n"
 "                     on. Just be careful so that the content  doesn't  contain\n"
 , stdout);
  fputs(
-"                     any  =  or  @  letters, as that will then make the syntax\n"
+"                     any  =  or  @  symbols, as that will then make the syntax\n"
 "                     match one of the other cases below!\n"
 "\n"
 "              =content\n"
 "                     This will make curl URL-encode the content and pass  that\n"
-"                     on. The preceding = letter is not included in the data.\n"
+"                     on. The preceding = symbol is not included in the data.\n"
 "\n"
 "              name=content\n"
 "                     This  will make curl URL-encode the content part and pass\n"
 , stdout);
  fputs(
 "                     that on. Note that the name part is expected to  be  URL-\n"
