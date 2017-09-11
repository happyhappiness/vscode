    double latlong[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (!extractLatLongOrReply(c, c->argv + 2, latlong))
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (!latLongFromMember(zobj, member, latlong)) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
