int
main(argc, argv)
int argc;
char *argv[];
{
    int i;
    int c;
    int dt;
    int j;
    fd_set R, R2;
    struct timeval start;
    struct timeval last;
    struct timeval to;
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    progname = xstrdup(argv[0]);
    gettimeofday(&now, NULL);
    start = last = now;
    custom_header = xstrdup("");
    while ((c = getopt(argc, argv, "ap:h:H:n:icrl:L:t:")) != -1) {
        switch (c) {
        case 'a':
            opt_accel = 1;
            break;
        case 'p':
            proxy_port = atoi(optarg);
            break;
        case 'h':
            proxy_addr = xstrdup(optarg);
            break;
        case 'n':
            max_connections = atoi(optarg);
            break;
        case 'i':
            opt_ims = 1;
            break;
        case 'l':
            lifetime = (time_t) atoi(optarg);
            break;
        case 'L':
            process_lifetime = (time_t) atoi(optarg);
            break;
        case 'c':
            opt_checksum = 1;
            break;
        case 't':
            trace_file = fopen(optarg, "a");
            assert(trace_file);
            setbuf(trace_file, NULL);
            break;
        case 'r':
            opt_range = 1;
            break;
        case 'H':
            custom_header = realloc(custom_header, strlen(custom_header) + strlen(optarg) + 2 + 1);
            strcat(custom_header, optarg);
            strcat(custom_header, "\r\n");
            break;
        default:
            usage();
            return 1;
        }
    }
    fd_open(0, read_url, NULL, NULL);
    nfds--;
    signal(SIGINT, sig_intr);
    signal(SIGPIPE, SIG_IGN);
    FD_ZERO(&R2);
    while (nfds || FD[0].cb) {
        FD_ZERO(&R);
        to.tv_sec = 0;
        to.tv_usec = 100000;
        if (nfds < max_connections && FD[0].cb)
            FD_SET(0, &R);
        for (i = 1; i <= maxfd; i++) {
            if (FD[i].cb == NULL)
                continue;
            if (now.tv_sec - FD[i].start > lifetime) {
                fprintf(stderr, "WARNING: fd %d lifetime timeout\n", i);
                fd_close(i);
                continue;
            }
            FD_SET(i, &R);
        }
        if (select(maxfd + 1, &R, NULL, NULL, &to) < 0) {
            fprintf(stderr, "maxfd=%d\n", maxfd);
            if (errno != EINTR)
                perror("select");
            continue;
        }
        gettimeofday(&now, NULL);
        for (i = 0; i <= maxfd; i++) {
            if (!FD_ISSET(i, &R))
                continue;
            FD[i].cb(i, FD[i].data);
            if (nfds < max_connections && FD[0].cb) {
                j = 0;
                FD_SET(0, &R2);
                to.tv_sec = 0;
                to.tv_usec = 0;
                if (select(1, &R2, NULL, NULL, &to) == 1)
                    FD[0].cb(0, FD[0].data);
            }
        }
        if (now.tv_sec > last.tv_sec) {
            last = now;
            dt = (int) (now.tv_sec - start.tv_sec);
            printf("T+ %6d: %9d req (%+4d), %4d conn, %3d/sec avg, %dmb, %dkb/sec avg\n",
                   dt,
                   nrequests,
                   reqpersec,
                   nfds,
                   (int) (nrequests / dt),
                   (int) (total_bytes_read / 1024 / 1024),
                   (int) (total_bytes_read / 1024 / dt));
            reqpersec = 0;
            /*
             * if (dt > process_lifetime)
             *     exit(0);
             */
        }
    }
    printf("Exiting normally\n");
    return 0;
}