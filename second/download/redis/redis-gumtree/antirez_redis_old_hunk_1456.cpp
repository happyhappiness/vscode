    georadiusGeneric(c, RADIUS_MEMBER);
}

/* GEODECODE score */
void geodecodeCommand(redisClient *c) {
    GeoHashBits geohash;
    if (getLongLongFromObjectOrReply(c, c->argv[1], (long long *)&geohash.bits,
                                     NULL) != REDIS_OK)
        return;

    GeoHashArea area;
    geohash.step = GEO_STEP_MAX;
    geohashDecodeWGS84(geohash, &area);

    double lon = (area.longitude.min + area.longitude.max) / 2;
    double lat = (area.latitude.min + area.latitude.max) / 2;

    /* Returning three nested replies */
    addReplyMultiBulkLen(c, 3);

    /* First, the minimum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.longitude.min);
    addReplyDouble(c, area.latitude.min);

    /* Next, the maximum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.longitude.max);
    addReplyDouble(c, area.latitude.max);

    /* Last, the averaged center of this bounding box */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, lon);
    addReplyDouble(c, lat);
}

/* GEOENCODE long lat [radius unit] */
void geoencodeCommand(redisClient *c) {
    double radius_meters = 0;
    if (c->argc == 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
            return;
    } else if (c->argc == 4 || c->argc > 5) {
        addReplyError(c, "syntax error, try: GEOENCODE x y [radius unit]");
        return;
    }

    double xy[2];
    if (extractLongLatOrReply(c, c->argv + 1, xy) == REDIS_ERR) return;

    /* Encode long/lat into our geohash */
    GeoHashBits geohash;
    uint8_t step = geohashEstimateStepsByRadius(radius_meters,0);
    geohashEncodeWGS84(xy[0], xy[1], step, &geohash);

    /* Align the hash to a valid 52-bit integer based on step size */
    GeoHashFix52Bits bits = geohashAlign52Bits(geohash);

    /* Decode the hash so we can return its bounding box */
    GeoHashArea area;
    geohashDecodeWGS84(geohash, &area);

    double lon = (area.longitude.min + area.longitude.max) / 2;
    double lat = (area.latitude.min + area.latitude.max) / 2;

    /* Return four nested multibulk replies. */
    addReplyMultiBulkLen(c, 5);

    /* Return the binary geohash we calculated as 52-bit integer */
    addReplyLongLong(c, bits);

    /* Return the minimum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.longitude.min);
    addReplyDouble(c, area.latitude.min);

    /* Return the maximum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.longitude.max);
    addReplyDouble(c, area.latitude.max);

    /* Return the averaged center */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, lon);
    addReplyDouble(c, lat);

    /* Return the two scores to query to get the range from the sorted set. */
    GeoHashFix52Bits min, max;
    scoresOfGeoHashBox(geohash,&min,&max);
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, min);
    addReplyDouble(c, max);
}

/* GEOHASH key ele1 ele2 ... eleN
 *
 * Returns an array with an 11 characters geohash representation of the
