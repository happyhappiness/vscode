        addReplyError(c,"This instance has cluster support disabled");
        return;
    }
    c->flags |= REDIS_ASKING;
    addReply(c,shared.ok);
}

