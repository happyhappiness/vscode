static void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [options] [http"
#ifdef USE_SSL
	    "[s]"
#endif
	    "://]hostname[:port]/path\n", progname);
    fprintf(stderr, "Options are:\n");
    fprintf(stderr, "    -n requests     Number of requests to perform\n");
    fprintf(stderr, "    -c concurrency  Number of multiple requests to make\n");
    fprintf(stderr, "    -t timelimit    Seconds to max. wait for responses\n");
    fprintf(stderr, "    -p postfile     File containing data to POST\n");
    fprintf(stderr, "    -T content-type Content-type header for POSTing\n");
    fprintf(stderr, "    -v verbosity    How much troubleshooting info to print\n");
    fprintf(stderr, "    -w              Print out results in HTML tables\n");
    fprintf(stderr, "    -i              Use HEAD instead of GET\n");
    fprintf(stderr, "    -x attributes   String to insert as table attributes\n");
    fprintf(stderr, "    -y attributes   String to insert as tr attributes\n");
    fprintf(stderr, "    -z attributes   String to insert as td or th attributes\n");
    fprintf(stderr, "    -C attribute    Add cookie, eg. 'Apache=1234. (repeatable)\n");
    fprintf(stderr, "    -H attribute    Add Arbitrary header line, eg. 'Accept-Encoding: gzip'\n");
    fprintf(stderr, "                    Inserted after all normal header lines. (repeatable)\n");
    fprintf(stderr, "    -A attribute    Add Basic WWW Authentication, the attributes\n");
    fprintf(stderr, "                    are a colon separated username and password.\n");
    fprintf(stderr, "    -P attribute    Add Basic Proxy Authentication, the attributes\n");
    fprintf(stderr, "                    are a colon separated username and password.\n");
    fprintf(stderr, "    -X proxy:port   Proxyserver and port number to use\n");
    fprintf(stderr, "    -V              Print version number and exit\n");
    fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");
    fprintf(stderr, "    -d              Do not show percentiles served table.\n");
    fprintf(stderr, "    -S              Do not show confidence estimators and warnings.\n");
    fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
    fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
#ifdef USE_SSL
    fprintf(stderr, "    -s              Use httpS instead of HTTP (SSL)\n");
#endif
    fprintf(stderr, "    -h              Display usage information (this message)\n");
    exit(EINVAL);
}