        port = atoi(p);
    return 0;
}

/* ------------------------------------------------------- */

/* read data to POST from file, save contents and length */

static int open_postfile(char *pfile)
{
    int postfd, status;
    struct stat postfilestat;

    if ((postfd = open(pfile, O_RDONLY)) == -1) {
        printf("Invalid postfile name (%s)\n", pfile);
        return errno;
    }
    if ((status = fstat(postfd, &postfilestat)) == -1) {
        perror("Can\'t stat postfile\n");
        return status;
    }
    postdata = malloc(postfilestat.st_size);
    if (!postdata) {
        printf("Can\'t alloc postfile buffer\n");
        return ENOMEM;
    }
    if (read(postfd, postdata, postfilestat.st_size) != postfilestat.st_size) {
        printf("error reading postfilen");
        return EIO;
    }
    postlen = postfilestat.st_size;
    return 0;
}

/* ------------------------------------------------------- */

extern char *optarg;
extern int optind, opterr, optopt;

/* sort out command-line args and call test */
int main(int argc, char **argv)
{
    int c, r;
    optind = 1;
    while ((c = getopt(argc, argv, "n:c:t:T:p:v:kVh")) > 0) {
        switch (c) {
        case 'n':
            requests = atoi(optarg);
            if (!requests) {
                err("Invalid number of requests\n");
            }
            break;
        case 'k':
            keepalive = 1;
            break;
        case 'c':
            concurrency = atoi(optarg);
            break;
        case 'p':
            if (0 == (r = open_postfile(optarg))) {
                posting = 1;
            }
	    else if (postdata) {
                exit(r);
	    }
            break;
        case 'v':
            verbosity = atoi(optarg);
            break;
        case 't':
            tlimit = atoi(optarg);
            requests = MAX_REQUESTS;    /* need to size data array on something */
            break;
        case 'T':
            strcpy(content_type, optarg);
            break;
        case 'V':
            copyright();
            exit(0);
            break;
        case 'h':
            usage(argv[0]);
            break;
++ apache_1.3.2/src/support/htdigest.c	1998-08-03 17:15:32.000000000 +0800
