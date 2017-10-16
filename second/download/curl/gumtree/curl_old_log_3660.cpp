fputs(
"              allow  curl to ftp to the machine host.domain.com with user name\n"
"              'myself' and password 'secret' should look similar to:\n"
"\n"
"              machine host.domain.com login myself password secret\n"
"\n"
"              If this option is used twice,  the  second  will  again  disable\n"
"              netrc usage.\n"
"\n"
"       --netrc-optional\n"
"              Very  similar to --netrc, but this option makes the .netrc usage\n"
"              optional and not mandatory as the --netrc does.\n"
"\n"
, stdout);