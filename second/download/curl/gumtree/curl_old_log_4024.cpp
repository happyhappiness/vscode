fputs(
"  Note that curl cannot use persistent connections for transfers that are used\n"
"  in subsequence curl invokes. Try to stuff as many URLs as possible on the\n"
"  same command line if they are using the same host, as that'll make the\n"
"  transfers faster. If you use a http proxy for file transfers, practically\n"
"  all transfers will be persistent.\n"
"\n"
"MULTIPLE TRANSFERS WITH A SINGLE COMMAND LINE\n"
"\n"
"  As is mentioned above, you can download multiple files with one command line\n"
, stdout);