    return mst;
}

static void printStringRepr(char *s, int len) {
    printf("\"");
    while(len--) {
        switch(*s) {
        case '\\':
        case '"':
            printf("\\%c",*s);
            break;
        case '\n': printf("\\n"); break;
        case '\r': printf("\\r"); break;
        case '\t': printf("\\t"); break;
        case '\a': printf("\\a"); break;
        case '\b': printf("\\b"); break;
        default:
            if (isprint(*s))
                printf("%c",*s);
            else
                printf("\\x%02x",(unsigned char)*s);
            break;
        }
        s++;
    }
    printf("\"");
}

/*------------------------------------------------------------------------------
 * Networking / parsing
 *--------------------------------------------------------------------------- */

/* Connect to the client. If force is not zero the connection is performed
 * even if there is already a connected socket. */
static int cliConnect(int force) {
    char err[ANET_ERR_LEN];
    static int fd = ANET_ERR;

    if (fd == ANET_ERR || force) {
        if (force) close(fd);
        if (config.hostsocket == NULL) {
            fd = anetTcpConnect(err,config.hostip,config.hostport);
        } else {
            fd = anetUnixConnect(err,config.hostsocket);
        }
        if (fd == ANET_ERR) {
            fprintf(stderr,"Could not connect to Redis at ");
            if (config.hostsocket == NULL)
                fprintf(stderr,"%s:%d: %s",config.hostip,config.hostport,err);
            else
                fprintf(stderr,"%s: %s",config.hostsocket,err);
            return -1;
        }
        anetTcpNoDelay(NULL,fd);
    }
    return fd;
}

static sds cliReadLine(int fd) {
    sds line = sdsempty();

    while(1) {
        char c;
        ssize_t ret;

        ret = read(fd,&c,1);
        if (ret <= 0) {
            sdsfree(line);
            return NULL;
        } else if ((ret == 0) || (c == '\n')) {
            break;
        } else {
            line = sdscatlen(line,&c,1);
        }
    }
    return sdstrim(line,"\r\n");
}

static int cliReadSingleLineReply(int fd, int quiet) {
    sds reply = cliReadLine(fd);

    if (reply == NULL) return 1;
    if (!quiet)
        printf("%s", reply);
    sdsfree(reply);
    return 0;
}

static int cliReadBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    char *reply, crlf[2];
    int bulklen;

    if (replylen == NULL) return 1;
    bulklen = atoi(replylen);
    if (bulklen == -1) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    reply = zmalloc(bulklen);
    anetRead(fd,reply,bulklen);
    anetRead(fd,crlf,2);
    if (config.raw_output || !config.tty) {
        if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
            zfree(reply);
            return 1;
        }
    } else {
        /* If you are producing output for the standard output we want
         * a more interesting output with quoted characters and so forth */
        printStringRepr(reply,bulklen);
    }
    zfree(reply);
    return 0;
}

static int cliReadMultiBulkReply(int fd) {
    sds replylen = cliReadLine(fd);
    int elements, c = 1;
    int retval = 0;

    if (replylen == NULL) return 1;
    elements = atoi(replylen);
    if (elements == -1) {
        sdsfree(replylen);
        printf("(nil)\n");
        return 0;
    }
    if (elements == 0) {
        printf("(empty list or set)\n");
    }
    while(elements--) {
        if (config.tty) printf("%d. ", c);
        if (cliReadReply(fd)) retval = 1;
        if (elements) printf("%c",config.mb_sep);
        c++;
    }
    return retval;
}

static int cliReadReply(int fd) {
    char type;
    int nread;

    if ((nread = anetRead(fd,&type,1)) <= 0) {
        if (config.shutdown) return 0;
        if (config.interactive &&
            (nread == 0 || (nread == -1 && errno == ECONNRESET)))
        {
            return ECONNRESET;
        } else {
            printf("I/O error while reading from socket: %s",strerror(errno));
            exit(1);
        }
    }
    switch(type) {
    case '-':
        if (config.tty) printf("(error) ");
        cliReadSingleLineReply(fd,0);
        return 1;
    case '+':
        return cliReadSingleLineReply(fd,0);
    case ':':
        if (config.tty) printf("(integer) ");
        return cliReadSingleLineReply(fd,0);
    case '$':
        return cliReadBulkReply(fd);
    case '*':
        return cliReadMultiBulkReply(fd);
    default:
        printf("protocol error, got '%c' as reply type byte", type);
        return 1;
    }
}

static int selectDb(int fd) {
    int retval;
    sds cmd;
    char type;

    if (config.dbnum == 0)
        return 0;

    cmd = sdsempty();
    cmd = sdscatprintf(cmd,"SELECT %d\r\n",config.dbnum);
    anetWrite(fd,cmd,sdslen(cmd));
    anetRead(fd,&type,1);
    if (type <= 0 || type != '+') return 1;
    retval = cliReadSingleLineReply(fd,1);
    if (retval) {
        return retval;
    }
    return 0;
}

static void showInteractiveHelp(void) {
