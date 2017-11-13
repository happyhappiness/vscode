fputs(
"              the screen and shows a percentage if the transfer size is known.\n"
"              For transfers without a known size, it will instead  output  one\n"
"              '#' character for every 1024 bytes transferred.\n"
"\n"
"       --proto-default <protocol>\n"
"              Tells curl to use protocol for any URL missing a scheme name.\n"
"\n"
"              Example:\n"
"\n"
"               curl --proto-default https ftp.mozilla.org\n"
"\n"
"              An  unknown  or  unsupported  protocol causes error CURLE_UNSUP-\n"
, stdout);