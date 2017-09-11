        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"stop-writes-on-bgsave-error",0)) {
        addReplyBulkCString(c,"stop-writes-on-bgsave-error");
        addReplyBulkCString(c,server.stop_writes_on_bgsave_err ? "yes" : "no");
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
