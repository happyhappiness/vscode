        if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
            stopAppendOnly();
        } else if (enable && server.aof_state == REDIS_AOF_OFF) {
            if (startAppendOnly() == REDIS_ERR) {
                addReplyError(c,
                    "Unable to turn on AOF. Check server logs.");
                return;
