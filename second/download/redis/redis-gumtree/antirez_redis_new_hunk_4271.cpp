        if ((pattern[0] == '*' && pattern[1] == '\0') ||
            stringmatchlen(pattern,plen,key,sdslen(key),0)) {
            if (expireIfNeeded(c->db,keyobj) == 0) {
                addReplyBulkLen(c,keyobj);
                addReply(c,keyobj);
                addReply(c,shared.crlf);
                numkeys++;
            }
        }
    }
    dictReleaseIterator(di);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
}

static void dbsizeCommand(redisClient *c) {
