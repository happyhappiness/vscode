    close(s); /* Close the file descriptor ASAP as fsync() may take time. */
    fsync(fd);
    fprintf(stderr,"Transfer finished with success.\n");
    exit(0);
}

static void pipeMode(void) {
    int fd = context->fd;
    long long errors = 0, replies = 0, obuf_len = 0, obuf_pos = 0;
    char ibuf[1024*16], obuf[1024*16]; /* Input and output buffers */
    char aneterr[ANET_ERR_LEN];
    redisReader *reader = redisReaderCreate();
