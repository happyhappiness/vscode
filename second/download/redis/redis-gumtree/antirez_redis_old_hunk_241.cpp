        addReplyDouble(c,mh->dataset_perc);

        freeMemoryOverheadData(mh);
    } else if (!strcasecmp(c->argv[1]->ptr,"help") && c->argc == 2) {
        addReplyMultiBulkLen(c,2);
        addReplyBulkCString(c,
        "MEMORY USAGE <key> [SAMPLES <count>] - Estimate memory usage of key");
        addReplyBulkCString(c,
        "MEMORY OVERHEAD                      - Show memory usage details");
    } else {
        addReplyError(c,"Syntax error. Try MEMORY HELP");
    }
