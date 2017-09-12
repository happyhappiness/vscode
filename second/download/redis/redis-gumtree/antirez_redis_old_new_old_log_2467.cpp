snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d[%d]> ",
            config.hostip, config.hostport, config.dbnum);