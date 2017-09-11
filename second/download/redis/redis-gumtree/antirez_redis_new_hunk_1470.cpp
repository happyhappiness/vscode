        return;
    }

    /* Find long/lat to use for radius search based on inquiry type */
    int base_args;
    double xy[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (extractLongLatOrReply(c, c->argv + 2, xy) == REDIS_ERR)
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (longLatFromMember(zobj, member, xy) == REDIS_ERR) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
