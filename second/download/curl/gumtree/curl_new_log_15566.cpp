fputs(
"  libcurl will attempt to use persistent connections for the transfers so that\n"
"  the second transfer to the same host can use the same connection that was\n"
"  already initiated and was left open in the previous transfer. This greatly\n"
"  decreases connection time for all but the first transfer and it makes a far\n"
"  better use of the network.\n"
"\n"
"  Note that curl cannot use persistent connections for transfers that are used\n"
"  in subsequence curl invokes. Try to stuff as many URLs as possible on the\n"
, stdout);