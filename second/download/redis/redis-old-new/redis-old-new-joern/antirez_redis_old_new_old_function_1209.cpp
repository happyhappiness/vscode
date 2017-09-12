void geoEncodeCommand(redisClient *c) {
    double radius_meters = 0;
    if (c->argc >= 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
            return;
    } else if (c->argc == 4) {
        addReplyError(c, "must provide units when asking for radius encode");
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
#ifdef DEBUG
    printf("Decoding with step size: %d\n", geohash.step);
#endif
    GeoHashArea area;
    geohashDecodeWGS84(geohash, &area);

    double lon = (area.longitude.min + area.longitude.max) / 2;
    double lat = (area.latitude.min + area.latitude.max) / 2;

    /* Return four nested multibulk replies. */
    addReplyMultiBulkLen(c, 4);

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
}