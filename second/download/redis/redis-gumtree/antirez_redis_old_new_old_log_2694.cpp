addReplyErrorFormat(c,"MIGRATE failed, tmp file creation error: %s.",
            strerror(errno));