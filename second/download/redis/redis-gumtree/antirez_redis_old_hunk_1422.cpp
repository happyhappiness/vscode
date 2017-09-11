            j++;
        }
        if (server.sentinel_mode && configfile && *configfile == '-') {
            redisLog(REDIS_WARNING,
                "Sentinel config from STDIN not allowed.");
            redisLog(REDIS_WARNING,
                "Sentinel needs config file on disk to save state.  Exiting...");
            exit(1);
        }
