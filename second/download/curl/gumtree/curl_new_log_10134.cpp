fputs(
"  that the above operation must be completed in whole within 30 minutes:\n"
"\n"
"        curl -m 1800 -Y 3000 -y 60 www.far-away-site.com\n"
"\n"
"  Forcing curl not to transfer data faster than a given rate is also possible,\n"
"  which might be useful if you're using a limited bandwidth connection and you\n"
"  don't want your transfer to use all of it (sometimes referred to as\n"
"  \"bandwidth throttle\").\n"
"\n"
"  Make curl transfer data no faster than 10 kilobytes per second:\n"
"\n"
, stdout);