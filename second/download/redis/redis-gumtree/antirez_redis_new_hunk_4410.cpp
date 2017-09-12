    }
    if ((fd = cliConnect()) == -1) return 1;

    /* Select db number */
    retval = selectDb(fd);
    if (retval) {
        fprintf(stderr,"Error setting DB num\n");
        return 1;
    }
 
    while(config.repeat--) {
        /* Build the command to send */
        cmd = sdsempty();
