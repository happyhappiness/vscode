        stats = sdscat(stats,buf);

        addReplyBulkSds(c,stats);
    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
#if defined(USE_JEMALLOC)
        if (!strcasecmp(c->argv[2]->ptr, "info")) {
            sds info = sdsempty();
            je_malloc_stats_print(inputCatSds, &info, NULL);
            addReplyBulkSds(c, info);
        } else if (!strcasecmp(c->argv[2]->ptr, "purge")) {
            char tmp[32];
            unsigned narenas = 0;
            size_t sz = sizeof(unsigned);
            if (!je_mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
                sprintf(tmp, "arena.%d.purge", narenas);
                if (!je_mallctl(tmp, NULL, 0, NULL, 0)) {
                    addReply(c, shared.ok);
                    return;
                }
            }
            addReplyError(c, "Error purging dirty pages");
        } else {
            addReplyErrorFormat(c, "Valid jemalloc debug fields: info, purge");
        }
#else
        addReplyErrorFormat(c, "jemalloc support not available");
#endif
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
            (char*)c->argv[1]->ptr);
