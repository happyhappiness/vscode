        /* Ignore the error if any, not all the Redis versions support
         * REPLCONF listening-port. */
        if (err[0] == '-') {
            serverLog(LL_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
        }
        sdsfree(err);
    }
