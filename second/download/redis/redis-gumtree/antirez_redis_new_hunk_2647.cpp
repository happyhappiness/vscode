                          (char*)c->argv[1]->ptr);
}

void sentinelInfoCommand(redisClient *c) {
    char *section = c->argc == 2 ? c->argv[1]->ptr : "default";
    sds info = sdsempty();
    int defsections = !strcasecmp(section,"default");
    int sections = 0;

    if (c->argc > 2) {
        addReply(c,shared.syntaxerr);
        return;
    }

    if (!strcasecmp(section,"server") || defsections) {
        if (sections++) info = sdscat(info,"\r\n");
        sds serversection = genRedisInfoString("server");
        info = sdscatlen(info,serversection,sdslen(serversection));
        sdsfree(serversection);
    }

    if (!strcasecmp(section,"sentinel") || defsections) {
        dictIterator *di;
        dictEntry *de;
        int master_id = 0;

        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Sentinel\r\n"
            "sentinel_masters:%lu\r\n"
            "sentinel_tilt:%d\r\n"
            "sentinel_running_scripts:%d\r\n"
            "sentinel_scripts_queue_length:%ld\r\n",
            dictSize(sentinel.masters),
            sentinel.tilt,
            sentinel.running_scripts,
            listLength(sentinel.scripts_queue));

        di = dictGetIterator(sentinel.masters);
        while((de = dictNext(di)) != NULL) {
            sentinelRedisInstance *ri = dictGetVal(de);
            char *status = "ok";

            if (ri->flags & SRI_O_DOWN) status = "odown";
            else if (ri->flags & SRI_S_DOWN) status = "sdown";
            info = sdscatprintf(info,
                "master%d:name=%s,status=%s,address=%s:%d,"
                "slaves=%lu,sentinels=%lu\r\n",
                master_id++, ri->name, status,
                ri->addr->ip, ri->addr->port,
                dictSize(ri->slaves),
                dictSize(ri->sentinels)+1);
        }
        dictReleaseIterator(di);
    }

    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
        (unsigned long)sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}

/* ===================== SENTINEL availability checks ======================= */

/* Is this instance down from our point of view? */
