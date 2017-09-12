len = snprintf(config.prompt,sizeof(config.prompt),
                       strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                       config.hostip, config.hostport);