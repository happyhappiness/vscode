        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                       config.hostsocket);
    else
        len = anetFormatAddr(config.prompt, sizeof(config.prompt),
                           config.hostip, config.hostport);
    /* Add [dbnum] if needed */
    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
