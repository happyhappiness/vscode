        }
        addReplyBulkCBuffer(c,o,sdslen(o));
        sdsfree(o);
    } else {
        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
    }
