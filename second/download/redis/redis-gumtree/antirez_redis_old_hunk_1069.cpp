            server.aof_buf = sdsempty();
        }

        server.aof_lastbgrewrite_status = REDIS_OK;

        serverLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
        /* Change state from WAIT_REWRITE to ON if needed */
