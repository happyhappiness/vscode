fputs(
"              there is no file part in the specified URL, Curl will append the\n"
"              local file name. NOTE that you must use a trailing / on the last\n"
"              directory  to really prove to Curl that there is no file name or\n"
"              curl will think that your last directory name is the remote file\n"
"              name to use. That will most likely cause the upload operation to\n"
"              fail. If this is used on a HTTP(S) server, the PUT command  will\n"
"              be used.\n"
"\n"
, stdout);