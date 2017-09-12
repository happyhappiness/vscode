static void slaveMode(void) {
    /* To start we need to send the SYNC command and return the payload.
     * The hiredis client lib does not understand this part of the protocol
     * and we don't want to mess with its buffers, so everything is performed
     * using direct low-level I/O. */
    int fd = context->fd;
    char buf[1024], *p;
    ssize_t nread;
    unsigned long long payload;

    /* Send the SYNC command. */
    write(fd,"SYNC\r\n",6);

    /* Read $<payload>\r\n, making sure to read just up to "\n" */
    p = buf;
    while(1) {
        nread = read(fd,p,1);
        if (nread <= 0) {
            fprintf(stderr,"Error reading bulk length while SYNCing\n");
            exit(1);
        }
        if (*p == '\n') break;
        p++;
    }
    *p = '\0';
    payload = strtoull(buf+1,NULL,10);
    if (!config.raw_output)
        printf("SYNC with master, discarding %lld bytes of bulk tranfer...\n",
            payload);

    /* Discard the payload. */
    while(payload) {
        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
        if (nread <= 0) {
            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
            exit(1);
        }
        payload -= nread;
    }
    if (!config.raw_output) printf("SYNC done. Logging commands from master.\n");

    /* Now we can use the hiredis to read the incoming protocol. */
    while (cliReadReply(config.raw_output) == REDIS_OK);
}