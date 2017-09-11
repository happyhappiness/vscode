                       strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                       config.hostip, config.hostport);
    /* Add [dbnum] if needed */
    if (config.dbnum != 0)
        len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
            config.dbnum);
    snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
