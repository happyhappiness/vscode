"        # default url to get\n"
"        url = \"http://help.with.curl.com/curlhelp.html\"\n"
"\n"
"  You can specify another config file to be read by using the -K/--config\n"
"  flag. If you set config file name to \"-\" it'll read the config from stdin,\n"
"  which can be handy if you want to hide options from being visible in process\n"
, stdout);
 fputs(
"  tables etc:\n"
"\n"
"        echo \"user = user:passwd\" | curl -K - http://that.secret.site.com\n"
"\n"
"EXTRA HEADERS\n"
"\n"
