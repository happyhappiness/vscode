    totlen = 1+intlen(argc)+2;
    for (j = 0; j < argc; j++) {
        len = argvlen ? argvlen[j] : strlen(argv[j]);
        totlen += 1+intlen(len)+2+len+2;
    }

    /* Build the command at protocol level */
    cmd = malloc(totlen+1);
    if (!cmd) redisOOM();
    pos = sprintf(cmd,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
        len = argvlen ? argvlen[j] : strlen(argv[j]);
