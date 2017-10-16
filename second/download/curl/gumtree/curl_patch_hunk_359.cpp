 "              encode the value of a form field you may use --data-urlencode.\n"
 "\n"
 "              If  any of these options is used more than once on the same com-\n"
 , stdout);
  fputs(
 "              mand line, the data pieces specified  will  be  merged  together\n"
-"              with  a  separating  &-letter.  Thus,  using  '-d name=daniel -d\n"
+"              with  a  separating  &-symbol.  Thus,  using  '-d name=daniel -d\n"
 "              skill=lousy'  would  generate  a  post  chunk  that  looks  like\n"
 "              'name=daniel&skill=lousy'.\n"
 "\n"
 "              If  you  start  the data with the letter @, the rest should be a\n"
 "              file name to read the data from, or - if you want curl  to  read\n"
 , stdout);
