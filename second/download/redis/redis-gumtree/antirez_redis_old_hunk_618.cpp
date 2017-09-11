        serverLog(LL_VERBOSE,
            "Background AOF rewrite signal handler took %lldus", ustime()-now);
    } else if (!bysignal && exitcode != 0) {
        server.aof_lastbgrewrite_status = C_ERR;

        serverLog(LL_WARNING,
            "Background AOF rewrite terminated with error");
    } else {
