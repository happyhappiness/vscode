addReplyErrorFormat(c,"DUMP failed, tmp file write error: %s.",
        strerror(errno));