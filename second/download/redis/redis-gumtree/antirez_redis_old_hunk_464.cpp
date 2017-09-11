            sds info = sdsempty();
            je_malloc_stats_print(inputCatSds, &info, NULL);
            addReplyBulkSds(c, info);
        } else {
            addReplyErrorFormat(c, "Valid jemalloc debug fields: info");
        }
#else
        addReplyErrorFormat(c, "jemalloc support not available");
