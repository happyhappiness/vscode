fputs(
"  flag. If you set config file name to \"-\" it'll read the config from stdin,\n"
"  which can be handy if you want to hide options from being visible in process\n"
"  tables etc:\n"
"\n"
"        echo \"user = user:passwd\" | curl -K - http://that.secret.site.com\n"
"\n"
"EXTRA HEADERS\n"
"\n"
"  When using curl in your own very special programs, you may end up needing\n"
"  to pass on your own custom headers when getting a web page. You can do\n"
"  this by using the -H flag.\n"
"\n"
, stdout);