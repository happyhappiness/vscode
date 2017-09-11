        return PSYNC_CONTINUE;
    }

    /* If we reach this point we received either an error since the master does
     * not understand PSYNC, or an unexpected reply from the master.
     * Return PSYNC_NOT_SUPPORTED to the caller in both cases. */

    if (strncmp(reply,"-ERR",4)) {
        /* If it's not an error, log the unexpected event. */
