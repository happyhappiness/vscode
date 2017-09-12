redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
                    "protocol error, got %s as reply type byte", byte));