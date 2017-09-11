    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, y);
    addReplyDouble(c, x);
}

void geoEncodeCommand(redisClient *c) {
    /* args 0-2: ["geoencode", lat, long];
     * optionals: [radius, units] */

    double radius_meters = 0;
    if (c->argc >= 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
            return;
    } else if (c->argc == 4) {
        addReplyError(c, "must provide units when asking for radius encode");
        return;
    }

    double latlong[2];
    if (!extractLatLongOrReply(c, c->argv + 1, latlong)) return;

    /* Encode lat/long into our geohash */
    GeoHashBits geohash;
