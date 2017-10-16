"              not try using EPSV.\n"
"\n"
"              --epsv can be used to explicitly enable EPRT again and --no-epsv\n"
"              is an alias for --disable-epsv.\n"
"\n"
"              Disabling EPSV only changes the passive behavior. If you want to\n"
"              switch to active mode you need to use -P, --ftp-port.\n"
"\n"
"       -e, --referer <URL>\n"
, stdout);
 fputs(
"              (HTTP) Sends the \"Referer Page\" information to the HTTP  server.\n"
"              This can also be set with the -H, --header flag of course.  When\n"
"              used with -L, --location you can append \";auto\" to the --referer\n"
"              URL to make curl automatically set the previous URL when it fol-\n"
"              lows a Location: header. The \";auto\" string can be  used  alone,\n"
"              even if you don't set an initial --referer.\n"
"\n"
, stdout);
 fputs(
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -E, --cert <certificate[:password]>\n"
"              (SSL)  Tells  curl  to use the specified client certificate file\n"
"              when getting a file with HTTPS, FTPS or another SSL-based proto-\n"
"              col.  The  certificate  must  be in PEM format.  If the optional\n"
"              password isn't specified, it will be queried for on  the  termi-\n"
, stdout);
 fputs(
