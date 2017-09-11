        return;
    }

    /* Find lat/long to use for radius search based on inquiry type */
    int base_args;
    double latlong[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (extractLatLongOrReply(c, c->argv + 2, latlong) == REDIS_ERR)
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (latLongFromMember(zobj, member, latlong) == REDIS_ERR) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
