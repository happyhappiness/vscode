            default:
                byte = sdscatrepr(sdsempty(),p,1);
                redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
                    "Protocol error, got %s as reply type byte", byte));
                sdsfree(byte);
                return -1;
            }
