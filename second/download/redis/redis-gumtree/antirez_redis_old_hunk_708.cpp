        if (reply != NULL) {
            serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
            sdsfree(reply);
            return PSYNC_WRITE_ERROR;
        }
        return PSYNC_WAIT_REPLY;
