    }
    fprintf(stderr,"SYNC done. Logging commands from master.\n");

    /* Now we can use hiredis to read the incoming protocol. */
    config.output = OUTPUT_CSV;
    while (cliReadReply(0) == REDIS_OK);
}

/* This function implements --rdb, so it uses the replication protocol in order
 * to fetch the RDB file from a remote server. */
static void getRDB(void) {
    int s = context->fd;
    int fd;
    unsigned long long payload = sendSync(s);
    char buf[4096];

    fprintf(stderr,"SYNC sent to master, writing %llu bytes to '%s'\n",
        payload, config.rdb_filename);

    /* Write to file. */
    if (!strcmp(config.rdb_filename,"-")) {
        fd = STDOUT_FILENO;
    } else {
        fd = open(config.rdb_filename, O_CREAT|O_WRONLY, 0644);
        if (fd == -1) {
            fprintf(stderr, "Error opening '%s': %s\n", config.rdb_filename,
                strerror(errno));
            exit(1);
        }
    }

    while(payload) {
        ssize_t nread, nwritten;
        
        nread = read(s,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
        if (nread <= 0) {
            fprintf(stderr,"I/O Error reading RDB payload from socket\n");
            exit(1);
        }
        nwritten = write(fd, buf, nread);
        if (nwritten != nread) {
            fprintf(stderr,"Error writing data to file: %s\n",
                strerror(errno));
            exit(1);
        }
        payload -= nread;
    }
    close(s); /* Close the file descriptor ASAP as fsync() may take time. */
    fsync(fd);
    fprintf(stderr,"Transfer finished with success.\n");
    exit(0);
}

static void pipeMode(void) {
    int fd = context->fd;
    long long errors = 0, replies = 0, obuf_len = 0, obuf_pos = 0;
