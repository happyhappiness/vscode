, stdout);
 fputs(
"              you're  doing. Remove an internal header by giving a replacement\n"
"              without content on the right  side  of  the  colon,  as  in:  -H\n"
"              \"Host:\".\n"
"\n"
"              curl  will  make  sure that each header you add/replace get sent\n"
"              with the proper end of line marker, you should thus not add that\n"
"              as a part of the header content: do not add newlines or carriage\n"
"              returns they will only mess things up for you.\n"
"\n"
, stdout);
 fputs(
"              See also the -A/--user-agent and -e/--referer options.\n"
"\n"
"              This option can be used  multiple  times  to  add/replace/remove\n"
