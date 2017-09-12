    return sdstrim(line,"\r\n");
}

static int cliReadSingleLineReply(int fd, int quiet) {
    sds reply = cliReadLine(fd);

    if (reply == NULL) return 1;
    if (!quiet)
        printf("%s\n", reply);
    return 0;
}

