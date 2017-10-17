fputs(
"       -e/--referer <URL>\n"
"              (HTTP) Sends the \"Referer Page\" information to  the\n"
"              HTTP   server.  This  can  also  be  set  with  the\n"
"              -H/--header  flag  of  course.   When   used   with\n"
"              -L/--location you can append \";auto\" to the referer\n"
"              URL to make curl automatically set the previous URL\n"
"              when  it  follows  a  Location: header. The \";auto\"\n"
"              string can be used alone, even if you don't set  an\n"
, stdout);