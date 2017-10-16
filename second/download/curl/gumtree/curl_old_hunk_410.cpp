"\n"
, stdout);
 fputs(
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -z/--time-cond <date expression>\n"
"              (HTTP/FTP) Request a file that has been modified later than  the\n"
"              given  time  and date, or one that has been modified before that\n"
"              time. The date expression can be all sorts of date strings or if\n"
"              it  doesn't  match  any  internal ones, it tries to get the time\n"
, stdout);
 fputs(
"              from a given file name  instead!  See  the  curl_getdate(3)  man\n"
"              pages for date expression details.\n"
"\n"
"              Start the date expression with a dash (-) to make it request for\n"
"              a document that is older than the given date/time, default is  a\n"
"              document that is newer than the specified date/time.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       --max-redirs <num>\n"
, stdout);
