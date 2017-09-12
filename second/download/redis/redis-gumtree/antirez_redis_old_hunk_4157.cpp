    int fd, j, retval = 0;
    sds cmd;

    config.raw_output = (rc->flags & CMDFLAG_RAWOUTPUT);
    if (!rc) {
        fprintf(stderr,"Unknown command '%s'\n",argv[0]);
        return 1;
    }

    if ((rc->arity > 0 && argc != rc->arity) ||
        (rc->arity < 0 && argc < -rc->arity)) {
