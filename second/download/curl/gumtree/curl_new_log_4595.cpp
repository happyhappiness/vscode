fputs(
"        curl -T - http://www.upload.com/myfile\n"
"\n"
"  Note that the http server must have been configured to accept PUT before\n"
"  this can be done successfully.\n"
"\n"
"  For other ways to do http data upload, see the POST section below.\n"
"\n"
"VERBOSE / DEBUG\n"
"\n"
"  If curl fails where it isn't supposed to, if the servers don't let you in,\n"
"  if you can't understand the responses: use the -v flag to get verbose\n"
"  fetching. Curl will output lots of info and what it sends and receives in\n"
, stdout);