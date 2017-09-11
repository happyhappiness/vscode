        sizes = sdscatprintf(sizes,"dictentry:%d ", (int)sizeof(dictEntry));
        sizes = sdscatprintf(sizes,"sdshdr:%d", (int)sizeof(struct sdshdr));
        addReplyBulkSds(c,sizes);
    } else if (!strcasecmp(c->argv[1]->ptr,"htstats") && c->argc == 3) {
        long dbid;
        sds stats = sdsempty();
        char buf[4096];

        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != REDIS_OK)
            return;
        if (dbid < 0 || dbid >= server.dbnum) {
            addReplyError(c,"Out of range database");
            return;
        }

        stats = sdscatprintf(stats,"[Dictionary HT]\n");
        dictGetStats(buf,sizeof(buf),server.db[dbid].dict);
        stats = sdscat(stats,buf);

        stats = sdscatprintf(stats,"[Expires HT]\n");
        dictGetStats(buf,sizeof(buf),server.db[dbid].expires);
        stats = sdscat(stats,buf);

        addReplyBulkSds(c,stats);
    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
#if defined(USE_JEMALLOC)
        if (!strcasecmp(c->argv[2]->ptr, "info")) {
