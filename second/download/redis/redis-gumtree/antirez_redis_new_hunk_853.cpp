        int enable = yesnotoi(o->ptr);

        if (enable == -1) goto badfmt;
        if (enable == 0 && server.aof_state != AOF_OFF) {
            stopAppendOnly();
        } else if (enable && server.aof_state == AOF_OFF) {
            if (startAppendOnly() == C_ERR) {
                addReplyError(c,
                    "Unable to turn on AOF. Check server logs.");
