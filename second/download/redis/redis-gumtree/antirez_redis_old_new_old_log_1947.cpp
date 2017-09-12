len = snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d",
                       config.hostip, config.hostport);