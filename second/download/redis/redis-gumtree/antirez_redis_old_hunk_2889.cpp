        addReplyBulkCString(c,s);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}

