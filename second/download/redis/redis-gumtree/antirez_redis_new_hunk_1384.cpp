    }

    /* Log its ID to make debugging of issues simpler. */
    serverLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);

    /* We want to generate a +monitor event for every configured master
     * at startup. */
