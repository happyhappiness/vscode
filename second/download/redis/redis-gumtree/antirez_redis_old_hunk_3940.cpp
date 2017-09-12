    }
    while(elements--) {
        if (config.tty) printf("%d. ", c);
        if (cliReadReply(fd)) return 1;
        if (elements) printf("%c",config.mb_sep);
        c++;
    }
    return 0;
}

static int cliReadReply(int fd) {
    char type;

    if (anetRead(fd,&type,1) <= 0) {
        if (config.shutdown) return 0;
        exit(1);
    }
    switch(type) {
    case '-':
