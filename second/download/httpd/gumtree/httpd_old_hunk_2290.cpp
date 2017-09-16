{

    fprintf(stderr, "Usage: %s [options] [http://]hostname[:port]/path\n", progname);

    fprintf(stderr, "Options are:\n");

    fprintf(stderr, "    -n requests     Number of requests to perform\n");

    fprintf(stderr, "    -c concurrency  Number of multiple requests to make\n");

    fprintf(stderr, "    -t timelimit    Seconds to max. wait for responses\n");

    fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");

    fprintf(stderr, "    -v              Display version and copyright information\n");

    fprintf(stderr, "    -h              Display usage information (this message)\n");

    exit(EINVAL);

}



/* ------------------------------------------------------- */



