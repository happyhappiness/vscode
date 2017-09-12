    }
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
}

void persistCommand(redisClient *c) {
    dictEntry *de;

    de = dictFind(c->db->dict,c->argv[1]->ptr);
    if (de == NULL) {
        addReply(c,shared.czero);
    } else {
        if (removeExpire(c->db,c->argv[1]))
            addReply(c,shared.cone);
        else
            addReply(c,shared.czero);
    }
}
