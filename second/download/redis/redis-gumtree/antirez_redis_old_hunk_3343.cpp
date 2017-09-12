            addReplyError(c, "DEBUG FLUSHCACHE called with diskstore off.");
            return;
        } else {
            emptyDb();
            addReply(c,shared.ok);
            return;
