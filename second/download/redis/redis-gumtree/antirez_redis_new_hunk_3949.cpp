    }
    while(elements--) {
        printf("%d. ", c);
        if (cliReadReply(fd)) retval = 1;
        c++;
    }
    return retval;
}

static int cliReadReply(int fd) {
