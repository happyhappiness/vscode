        return 1;
    }

    /* Login if necessary */
    retval = cliLogin(fd);
    if (retval) {
        fprintf(stderr,"Authentication failed\n");
        return 1;
    }

    while(config.repeat--) {
        /* Build the command to send */
        cmd = sdsempty();
