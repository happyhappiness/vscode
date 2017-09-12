redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "unknown item type '%d'", cur->type));