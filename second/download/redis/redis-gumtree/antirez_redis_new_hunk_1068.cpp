            serverLog(REDIS_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));
            return C_ERR;
        }
        serverLog(REDIS_NOTICE,
            "Background append only file rewriting started by pid %d",childpid);
