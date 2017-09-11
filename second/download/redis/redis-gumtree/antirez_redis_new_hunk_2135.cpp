            redisLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            redisLog(REDIS_WARNING,"CONFIG REWRITE executed with success.");
            addReply(c,shared.ok);
        }
    } else {
