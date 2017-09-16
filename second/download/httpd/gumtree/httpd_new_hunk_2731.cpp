{

    fprintf(stderr, "Usage: %s [options] [http://]hostname[:port]/path\n", progname);

    fprintf(stderr, "Options are:\n");

    fprintf(stderr, "    -n requests     Number of requests to perform\n");

    fprintf(stderr, "    -c concurrency  Number of multiple requests to make\n");

    fprintf(stderr, "    -t timelimit    Seconds to max. wait for responses\n");

    fprintf(stderr, "    -p postfile     File containg data to POST\n");

    fprintf(stderr, "    -T content-type Content-type header for POSTing\n");

    fprintf(stderr, "    -v verbosity    How much troubleshooting info to print\n");

    fprintf(stderr, "    -V              Print version number and exit\n");

    fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");

    fprintf(stderr, "    -h              Display usage information (this message)\n");

    exit(EINVAL);

}



/* ------------------------------------------------------- */



