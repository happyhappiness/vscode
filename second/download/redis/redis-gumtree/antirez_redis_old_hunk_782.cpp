
        server.aof_lastbgrewrite_status = C_OK;

        serverLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
        /* Change state from WAIT_REWRITE to ON if needed */
        if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
            server.aof_state = REDIS_AOF_ON;

        /* Asynchronously close the overwritten AOF. */
        if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);

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
    }

