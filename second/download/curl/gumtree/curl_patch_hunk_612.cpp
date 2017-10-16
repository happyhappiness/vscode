 " (*2) = This requires that the wb server supports at least HTTP/1.1. If it\n"
 "        doesn't, curl will say so.\n"
 "\n"
 "TIME CONDITIONS\n"
 "\n"
 " HTTP allows a client to specify a time condition for the document it\n"
-);
- puts(
 " requests. It is If-Modified-Since or If-Unmodified-Since. Curl allow you to\n"
 " specify them with the -z/--time-cond flag.\n"
 "\n"
 " For example, you can easily make a download that only gets performed if the\n"
 " remote file is newer than a local copy. It would be made like:\n"
 "\n"
