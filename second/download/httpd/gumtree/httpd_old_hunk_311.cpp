        port = atoi(p);
    return 0;
}

/* ------------------------------------------------------- */

extern char *optarg;
extern int optind, opterr, optopt;

/* sort out command-line args and call test */
int main(int argc, char **argv)
{
    int c;
    optind = 1;
    while ((c = getopt(argc, argv, "n:c:t:kvh")) > 0) {
        switch (c) {
        case 'n':
            requests = atoi(optarg);
            if (!requests) {
                printf("Invalid number of requests\n");
                exit(1);
            }
            break;
        case 'k':
            keepalive = 1;
            break;
        case 'c':
            concurrency = atoi(optarg);
            break;
        case 't':
            tlimit = atoi(optarg);
            requests = MAX_REQUESTS;    /* need to size data array on something */
            break;
        case 'v':
            copyright();
            exit(0);
            break;
        case 'h':
            usage(argv[0]);
            break;
