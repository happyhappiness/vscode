int
main(int argc, char *const argv[])
{
    int nstart = 0, kstart = 0;
    int nend = 0, kend = 0;
    char **nargs, **kargs;
    int fpid;
    int pkin[2];
    int pkout[2];
    int pnin[2];
    int pnout[2];

    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    if (argc ==1 || !strncasecmp(argv[1],"-h",2)) {
        usage();
        return 0;
    }

    int j = 1;
    if (!strncasecmp(argv[1],"-d",2)) {
        debug_enabled = 1;
        j = 2;
    }

    for (int i=j; i<argc; ++i) {
        if (!strncasecmp(argv[i],"--ntlm",6))
            nstart = i;
        if (!strncasecmp(argv[i],"--kerberos",10))
            kstart = i;
    }
    if (nstart > kstart) {
        kend = nstart-1;
        nend = argc-1;
    } else {
        kend = argc-1;
        nend = kstart-1;
    }
    if (nstart == 0 || kstart == 0 || kend-kstart <= 0 || nend-nstart <= 0 ) {
        usage();
        return 0;
    }

    if (debug_enabled)
        fprintf(stderr, "%s| %s: Starting version %s\n", LogTime(), PROGRAM,
                VERSION);

    if ((nargs = (char **)xmalloc((nend-nstart+1)*sizeof(char *))) == NULL) {
        fprintf(stderr, "%s| %s: Error allocating memory for ntlm helper\n", LogTime(), PROGRAM);
        return 1;
    }
    memcpy(nargs,argv+nstart+1,(nend-nstart)*sizeof(char *));
    nargs[nend-nstart]=NULL;
    if (debug_enabled) {
        fprintf(stderr, "%s| %s: NTLM command: ", LogTime(), PROGRAM);
        for (int i=0; i<nend-nstart; ++i)
            fprintf(stderr, "%s ", nargs[i]);
        fprintf(stderr, "\n");
    }
    if ((kargs = (char **)xmalloc((kend-kstart+1)*sizeof(char *))) == NULL) {
        fprintf(stderr, "%s| %s: Error allocating memory for kerberos helper\n", LogTime(), PROGRAM);
        return 1;
    }
    memcpy(kargs,argv+kstart+1,(kend-kstart)*sizeof(char *));
    kargs[kend-kstart]=NULL;
    if (debug_enabled) {
        fprintf(stderr, "%s| %s: Kerberos command: ", LogTime(), PROGRAM);
        for (int i=0; i<kend-kstart; ++i)
            fprintf(stderr, "%s ", kargs[i]);
        fprintf(stderr, "\n");
    }
    /*
       Fork Kerberos helper and NTLM helper and manage IO to send NTLM requests
       to the right helper. squid must keep session state
    */

    if (pipe(pkin) < 0) {
        fprintf(stderr, "%s| %s: Could not assign streams for pkin\n", LogTime(), PROGRAM);
        return 1;
    }
    if (pipe(pkout) < 0) {
        fprintf(stderr, "%s| %s: Could not assign streams for pkout\n", LogTime(), PROGRAM);
        return 1;
    }

    if  (( fpid = vfork()) < 0 ) {
        fprintf(stderr, "%s| %s: Failed first fork\n", LogTime(), PROGRAM);
        return 1;
    }

    if ( fpid == 0 ) {
        /* First Child for Kerberos helper */

        close(pkin[1]);
        dup2(pkin[0],STDIN_FILENO);
        close(pkin[0]);

        close(pkout[0]);
        dup2(pkout[1],STDOUT_FILENO);
        close(pkout[1]);

        setbuf(stdin, NULL);
        setbuf(stdout, NULL);

        execv(kargs[0], kargs);
        fprintf(stderr, "%s| %s: Failed execv for %s: %s\n", LogTime(), PROGRAM, kargs[0], strerror(errno));
        return 1;
    }

    close(pkin[0]);
    close(pkout[1]);

    if (pipe(pnin) < 0) {
        fprintf(stderr, "%s| %s: Could not assign streams for pnin\n", LogTime(), PROGRAM);
        return 1;
    }
    if (pipe(pnout) < 0) {
        fprintf(stderr, "%s| %s: Could not assign streams for pnout\n", LogTime(), PROGRAM);
        return 1;
    }

    if  (( fpid = vfork()) < 0 ) {
        fprintf(stderr, "%s| %s: Failed second fork\n", LogTime(), PROGRAM);
        return 1;
    }

    if ( fpid == 0 ) {
        /* Second Child for NTLM helper */

        close(pnin[1]);
        dup2(pnin[0],STDIN_FILENO);
        close(pnin[0]);

        close(pnout[0]);
        dup2(pnout[1],STDOUT_FILENO);
        close(pnout[1]);

        setbuf(stdin, NULL);
        setbuf(stdout, NULL);

        execv(nargs[0], nargs);
        fprintf(stderr, "%s| %s: Failed execv for %s: %s\n", LogTime(), PROGRAM, nargs[0], strerror(errno));
        return 1;
    }

    close(pnin[0]);
    close(pnout[1]);

    FILE *FDKIN=fdopen(pkin[1],"w");
    FILE *FDKOUT=fdopen(pkout[0],"r");

    FILE *FDNIN=fdopen(pnin[1],"w");
    FILE *FDNOUT=fdopen(pnout[0],"r");

    if (!FDKIN || !FDKOUT || !FDNIN || !FDNOUT) {
        fprintf(stderr, "%s| %s: Could not assign streams for FDKIN/FDKOUT/FDNIN/FDNOUT\n", LogTime(), PROGRAM);
        closeFds(FDKIN, FDKOUT, FDNIN, FDNOUT);
        return 1;
    }

    setbuf(FDKIN, NULL);
    setbuf(FDKOUT, NULL);
    setbuf(FDNIN, NULL);
    setbuf(FDNOUT, NULL);

    int result = processingLoop(FDKIN, FDKOUT, FDNIN, FDNOUT);
    closeFds(FDKIN, FDKOUT, FDNIN, FDNOUT);
    return result;
}