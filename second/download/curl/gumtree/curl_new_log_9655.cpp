fputs(
"  To have curl abort the download if the speed is slower than 3000 bytes per\n"
"  second for 1 minute, run:\n"
"\n"
"        curl -Y 3000 -y 60 www.far-away-site.com\n"
"\n"
"  This can very well be used in combination with the overall time limit, so\n"
"  that the above operation must be completed in whole within 30 minutes:\n"
"\n"
"        curl -m 1800 -Y 3000 -y 60 www.far-away-site.com\n"
"\n"
"  Forcing curl not to transfer data faster than a given rate is also possible,\n"
, stdout);