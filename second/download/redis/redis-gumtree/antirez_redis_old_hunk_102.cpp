    curarg = NULL;

    /* Add bytes needed to hold multi bulk count */
    totlen += 1+intlen(argc)+2;

    /* Build the command at protocol level */
    cmd = malloc(totlen+1);
    if (cmd == NULL) goto err;

    pos = sprintf(cmd,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
