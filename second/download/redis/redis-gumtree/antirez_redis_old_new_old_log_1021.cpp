serverLog(REDIS_WARNING,
            "Sentinel config file %s is not writable: %s. Exiting...",
            server.configfile,strerror(errno));