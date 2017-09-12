        printf("(empty list or set)\n");
    }
    while(elements--) {
        if (config.tty) printf("%d. ", c);
        if (cliReadReply(fd)) return 1;
        if (elements) printf("%c",config.mb_sep);
        c++;
    }
    return 0;
