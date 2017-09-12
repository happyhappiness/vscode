addReplyErrorFormat(c,"RESTORE failed, tmp file creation error: %s",
            strerror(errno));