    return sdstrim(line,"\r\n");
}

static int cliReadSingleLineReply(int fd) {
    sds reply = cliReadLine(fd);

    if (reply == NULL) return 1;
    printf("%s\n", reply);
    return 0;
}

