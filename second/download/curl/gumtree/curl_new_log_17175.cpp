puts(
"  Curl allows the user to set the transfer speed conditions that must be met\n"
"  to let the transfer keep going. By using the switch -y and -Y you\n"
"  can make curl abort transfers if the transfer speed is below the specified\n"
"  lowest limit for a specified time.\n"
"\n"
"  To have curl abort the download if the speed is slower than 3000 bytes per\n"
"  second for 1 minute, run:\n"
"\n"
"        curl -y 3000 -Y 60 www.far-away-site.com\n"
"\n"
"  This can very well be used in combination with the overall time limit, so\n"
);