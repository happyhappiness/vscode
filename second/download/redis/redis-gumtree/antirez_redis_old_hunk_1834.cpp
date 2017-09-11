                    strerror(errno));
            }
        } else {
            redisLog(REDIS_WARNING,
                "AOF loaded anyway because aof-load-truncated is enabled");
            goto loaded_ok;
        }
    }
    redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
