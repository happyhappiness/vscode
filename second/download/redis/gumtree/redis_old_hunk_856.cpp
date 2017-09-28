        return;
    }

    /* Find long/lat to use for radius search based on inquiry type */
    int base_args;
    double xy[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (extractLongLatOrReply(c, c->argv + 2, xy) == C_ERR)
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (longLatFromMember(zobj, member, xy) == C_ERR) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
    } else {
        addReplyError(c, "unknown georadius search type");
        return;
    }

    /* Extract radius and units from arguments */
    double radius_meters = 0, conversion = 1;
    if ((radius_meters = extractDistanceOrReply(c, c->argv + base_args - 2,
