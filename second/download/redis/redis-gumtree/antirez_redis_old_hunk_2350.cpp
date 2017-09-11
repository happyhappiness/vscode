        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                       config.hostsocket);
    else
        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d",
                       config.hostip, config.hostport);
    /* Add [dbnum] if needed */
    if (config.dbnum != 0)
