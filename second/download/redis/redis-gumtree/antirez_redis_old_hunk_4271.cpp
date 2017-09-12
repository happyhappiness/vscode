        if ((pattern[0] == '*' && pattern[1] == '\0') ||
            stringmatchlen(pattern,plen,key,sdslen(key),0)) {
            if (expireIfNeeded(c->db,keyobj) == 0) {
                if (numkeys != 0)
                    addReply(c,shared.space);
                addReply(c,keyobj);
                numkeys++;
                keyslen += sdslen(key);
            }
        }
    }
    dictReleaseIterator(di);
    lenobj->ptr = sdscatprintf(sdsempty(),"$%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
    addReply(c,shared.crlf);
}

static void dbsizeCommand(redisClient *c) {
