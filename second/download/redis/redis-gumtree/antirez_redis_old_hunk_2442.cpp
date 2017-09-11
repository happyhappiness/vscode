        o = createObject(REDIS_STRING,ci);
        addReplyBulk(c,o);
        decrRefCount(o);
    } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
               !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3)
    {
