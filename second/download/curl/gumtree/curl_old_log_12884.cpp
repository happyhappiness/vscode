fputs(
"              NEW_ENV=<var,val> Sets an environment variable.\n"
"\n"
"       -T, --upload-file <file>\n"
"              This  transfers  the  specified local file to the remote URL. If\n"
"              there is no file part in the specified URL, Curl will append the\n"
"              local file name. NOTE that you must use a trailing / on the last\n"
"              directory to really prove to Curl that there is no file name  or\n"
"              curl will think that your last directory name is the remote file\n"
, stdout);