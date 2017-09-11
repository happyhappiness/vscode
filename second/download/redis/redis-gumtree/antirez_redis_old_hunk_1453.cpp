        sizes = sdscatprintf(sizes,"dictentry:%d ", (int)sizeof(dictEntry));
        sizes = sdscatprintf(sizes,"sdshdr:%d", (int)sizeof(struct sdshdr));
        addReplyBulkSds(c,sizes);
    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
#if defined(USE_JEMALLOC)
        if (!strcasecmp(c->argv[2]->ptr, "info")) {
