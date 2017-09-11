    char buf[1024];

    fprintf(stderr,"SYNC with master, discarding %llu "
                   "bytes of bulk tranfer...\n", payload);

    /* Discard the payload. */
    while(payload) {
