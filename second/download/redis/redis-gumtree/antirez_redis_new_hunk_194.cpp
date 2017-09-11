        addReplyError(c,"Background save already in progress");
        return;
    }
    if (rdbSave(server.rdb_filename,NULL) == C_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
