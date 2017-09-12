    }
    decrRefCount(o);
    addReply(c,shared.ok);
    return;

badfmt: /* Bad format errors */
    addReplySds(c,sdscatprintf(sdsempty(),
        "-ERR invalid argument '%s' for CONFIG SET '%s'\r\n",
            (char*)o->ptr,
            (char*)c->argv[2]->ptr));
    decrRefCount(o);
}

static void configGetCommand(redisClient *c) {
