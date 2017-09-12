        fprintf(stderr,"Error setting DB num\n");
        return 1;
    }

    while(config.repeat--) {
        /* Build the command to send */
        cmd = sdsempty();
