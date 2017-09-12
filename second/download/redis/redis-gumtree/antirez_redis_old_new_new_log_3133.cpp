redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "No support for nested multi bulk replies with depth > 1"));