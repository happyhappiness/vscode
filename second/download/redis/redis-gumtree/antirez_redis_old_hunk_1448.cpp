        addReplySds(c,errstr);
    } else if (!strcasecmp(c->argv[1]->ptr,"structsize") && c->argc == 2) {
        sds sizes = sdsempty();
        sizes = sdscatprintf(sizes,"bits:%d ", (sizeof(void*) == 8)?64:32);
        sizes = sdscatprintf(sizes,"robj:%d ", (int)sizeof(robj));
        sizes = sdscatprintf(sizes,"dictentry:%d ", (int)sizeof(dictEntry));
        sizes = sdscatprintf(sizes,"sdshdr8:%d", (int)sizeof(struct sdshdr8));
        sizes = sdscatprintf(sizes,"sdshdr16:%d", (int)sizeof(struct sdshdr16));
        sizes = sdscatprintf(sizes,"sdshdr32:%d", (int)sizeof(struct sdshdr32));
        sizes = sdscatprintf(sizes,"sdshdr64:%d", (int)sizeof(struct sdshdr64));
        addReplyBulkSds(c,sizes);
    } else if (!strcasecmp(c->argv[1]->ptr,"htstats") && c->argc == 3) {
        long dbid;
