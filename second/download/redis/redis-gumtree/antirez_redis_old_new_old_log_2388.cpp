addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));