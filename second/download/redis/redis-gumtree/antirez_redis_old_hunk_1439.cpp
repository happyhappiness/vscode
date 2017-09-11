        addReplySds(c,errstr);
    } else if (!strcasecmp(c->argv[1]->ptr,"structsize") && c->argc == 2) {
        sds sizes = sdsempty();
        sizes = sdscatprintf(sizes,"bits:%d ", (sizeof(void*) == 8)?64:32);
        sizes = sdscatprintf(sizes,"robj:%d ", (int)sizeof(robj));
        sizes = sdscatprintf(sizes,"dictentry:%d ", (int)sizeof(dictEntry));
        sizes = sdscatprintf(sizes,"sdshdr:%d", (int)sizeof(struct sdshdr));
        addReplyBulkSds(c,sizes);
    } else if (!strcasecmp(c->argv[1]->ptr,"htstats") && c->argc == 3) {
        long dbid;
