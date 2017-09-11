        p++;
    }
    *p = '\0';
    payload = strtoull(buf+1,NULL,10);
    fprintf(stderr,"SYNC with master, discarding %lld bytes of bulk tranfer...\n",
            payload);

    /* Discard the payload. */
    while(payload) {
        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
        if (nread <= 0) {
            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
