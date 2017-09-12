        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
        } else {
            addReplyBulkLen(c,o);
            addReply(c,o);
            addReply(c,shared.crlf);
        }
