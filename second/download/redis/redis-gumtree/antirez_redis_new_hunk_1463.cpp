/* GEOENCODE long lat [radius unit] */
void geoEncodeCommand(redisClient *c) {
    double radius_meters = 0;
    if (c->argc == 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
            return;
    } else if (c->argc == 4 || c->argc > 5) {
        addReplyError(c, "syntax error, try: GEOENCODE x y [radius unit]");
        return;
    }

