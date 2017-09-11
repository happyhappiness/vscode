        return;
    }
    if (selectDb(c,id) == C_ERR) {
        addReplyError(c,"invalid DB index");
    } else {
        addReply(c,shared.ok);
    }
