            len++;
        }
    }
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",(unsigned long)len));
}

static void addReplyBulk(redisClient *c, robj *obj) {
