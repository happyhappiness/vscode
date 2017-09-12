                j, keys, vkeys);
        }
    }
    return info;
}

static void infoCommand(redisClient *c) {
    sds info = genRedisInfoString();
    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
