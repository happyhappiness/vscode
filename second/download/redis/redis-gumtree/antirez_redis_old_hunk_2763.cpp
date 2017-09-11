        sdsfree(buf);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}

