        clusterAddNode(n);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
        robj *o;
        sds ci = clusterGenNodesDescription();

        o = createObject(REDIS_STRING,ci);
        addReplyBulk(c,o);
        decrRefCount(o);
