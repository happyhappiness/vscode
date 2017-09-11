        p++;
    }
    *p = '\0';
    if (buf[0] == '-') {
        printf("SYNC with master failed: %s\n", buf);
        exit(1);
    }
    return strtoull(buf+1,NULL,10);
}

static void slaveMode(void) {
    int fd = context->fd;
    unsigned long long payload = sendSync(fd);
    char buf[1024];

    fprintf(stderr,"SYNC with master, discarding %llu "
                   "bytes of bulk tranfer...\n", payload);

    /* Discard the payload. */
    while(payload) {
        ssize_t nread;

        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
        if (nread <= 0) {
            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
