            d = sdscatprintf(d, "%02x",digest[j]);
        addReplyStatus(c,d);
        sdsfree(d);
    } else {
        addReplyError(c,
            "Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]");
