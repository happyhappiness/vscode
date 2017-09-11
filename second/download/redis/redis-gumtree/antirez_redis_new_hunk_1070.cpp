        serverLog(REDIS_VERBOSE,
            "Background AOF rewrite signal handler took %lldus", ustime()-now);
    } else if (!bysignal && exitcode != 0) {
        server.aof_lastbgrewrite_status = C_ERR;

        serverLog(REDIS_WARNING,
            "Background AOF rewrite terminated with error");
    } else {
        server.aof_lastbgrewrite_status = C_ERR;

        serverLog(REDIS_WARNING,
            "Background AOF rewrite terminated by signal %d", bysignal);
