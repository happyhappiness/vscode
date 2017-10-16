fputs(
"       --no-sessionid\n"
"              (SSL)  Disable curl's use of SSL session-ID caching.  By default\n"
"              all transfers are done using the cache. Note that while  nothing\n"
"              ever  should  get  hurt  by attempting to reuse SSL session-IDs,\n"
"              there seem to be broken SSL implementations in the wild that may\n"
"              require  you to disable this in order for you to succeed. (Added\n"
"              in 7.16.0)\n"
"\n"
, stdout);