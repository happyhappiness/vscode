addReplyErrorFormat(c,"MIGRATE failed, tmp file write error: %s.",
        strerror(errno));