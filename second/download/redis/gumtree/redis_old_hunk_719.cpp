
        stats = sdscatprintf(stats,"[Expires HT]\n");
        dictGetStats(buf,sizeof(buf),server.db[dbid].expires);
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
    }
}

/* =========================== Crash handling  ============================== */

void _serverAssert(char *estr, char *file, int line) {
    bugReportStart();
    serverLog(LL_WARNING,"=== ASSERTION FAILED ===");
    serverLog(LL_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
#ifdef HAVE_BACKTRACE
    server.assert_failed = estr;
    server.assert_file = file;
    server.assert_line = line;
    serverLog(LL_WARNING,"(forcing SIGSEGV to print the bug report.)");
#endif
    *((char*)-1) = 'x';
}

void _serverAssertPrintClientInfo(client *c) {
    int j;

    bugReportStart();
    serverLog(LL_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
    serverLog(LL_WARNING,"client->flags = %d", c->flags);
    serverLog(LL_WARNING,"client->fd = %d", c->fd);
