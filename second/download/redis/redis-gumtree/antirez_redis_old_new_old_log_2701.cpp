addReplyErrorFormat(c,"MIGRATE failed, tmp file read error: %s.",
        strerror(errno));