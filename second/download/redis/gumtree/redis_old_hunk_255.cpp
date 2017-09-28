    long id;

    if (getLongFromObjectOrReply(c, c->argv[1], &id,
        "invalid DB index") != REDIS_OK)
        return;

    if (selectDb(c,id) == REDIS_ERR) {
        addReplyError(c,"invalid DB index");
    } else {
        addReply(c,shared.ok);
    }
}
