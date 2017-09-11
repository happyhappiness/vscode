    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, y);
    addReplyDouble(c, x);

    if (withgeojson) {
        struct geojsonPoint gp = { .latitude = y,
                                   .longitude = x,
                                   .member = NULL };

        /* Return geojson Feature Point */
        latLongToGeojsonAndReply(c, &gp, NULL);

        /* Return geojson Feature Polygon */
        decodeGeohashToGeojsonBoundsAndReply(c, geohash.bits, &gp);
    }
}

void geoEncodeCommand(redisClient *c) {
    /* args 0-2: ["geoencode", lat, long];
     * optionals: [radius, units]
     * - AND / OR -
     * optional: [geojson] */

    int withgeojson = 0;
    for (int i = 3; i < c->argc; i++) {
        char *arg = c->argv[i]->ptr;
        if (!strncasecmp(arg, "withgeo", 7) || !strcasecmp(arg, "geojson") ||
            !strcasecmp(arg, "json") || !strcasecmp(arg, "withjson")) {
            withgeojson = 1;
            break;
        }
    }

    double radius_meters = 0;
    if (c->argc >= 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) <
            0) {
            return;
        }
    } else if (c->argc == 4 && !withgeojson) {
        addReplyError(c, "must provide units when asking for radius encode");
        return;
    }

    double latlong[2];
    if (!extractLatLongOrReply(c, c->argv + 1, latlong))
        return;

    /* Encode lat/long into our geohash */
    GeoHashBits geohash;
