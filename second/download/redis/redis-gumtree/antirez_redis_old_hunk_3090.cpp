        addReplyError(c,"increment or decrement would overflow");
        return;
    }
    o = createStringObjectFromLongLong(value);
    dbReplace(c->db,c->argv[1],o);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.colon);
    addReply(c,o);
    addReply(c,shared.crlf);
}

