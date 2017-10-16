 "        curl --limit-rate 10240 www.far-away-site.com\n"
 "\n"
 "  Or prevent curl from uploading data faster than 1 megabyte per second:\n"
 "\n"
 "        curl -T upload --limit-rate 1M ftp://uploadshereplease.com\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  When using the --limit-rate option, the transfer rate is regulated on a\n"
 "  per-second basis, which will cause the total transfer speed to become lower\n"
 "  than the given number. Sometimes of course substantially lower, if your\n"
 "  transfer stalls during periods.\n"
 "\n"
 "CONFIG FILE\n"
 "\n"
 "  Curl automatically tries to read the .curlrc file (or _curlrc file on win32\n"
 "  systems) from the user's home dir on startup.\n"
 "\n"
 "  The config file could be made up with normal command line switches, but you\n"
-);
- puts(
+, stdout);
+ fputs(
 "  can also specify the long options without the dashes to make it more\n"
 "  readable. You can separate the options and the parameter with spaces, or\n"
 "  with = or :. Comments can be used within the file. If the first letter on a\n"
 "  line is a '#'-letter the rest of the line is treated as a comment.\n"
 "\n"
 "  If you want the parameter to contain spaces, you must inclose the entire\n"
 "  parameter within double quotes (\"). Within those quotes, you specify a\n"
 "  quote as \\\".\n"
 "\n"
-);
- puts(
+, stdout);
+ fputs(
 "  NOTE: You must specify options and their arguments on the same line.\n"
 "\n"
 "  Example, set default time out and proxy in a config file:\n"
 "\n"
 "        # We want a 30 minute timeout:\n"
 "        -m 1800\n"
