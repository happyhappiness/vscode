            strlen(seldb),seldb);
        server.appendseldb = dictid;
    }
    /* Append the actual command */
    buf = sdscatprintf(buf,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
