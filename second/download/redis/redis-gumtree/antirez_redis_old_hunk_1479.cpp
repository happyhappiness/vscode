    return distance * to_meters;
}

/* Output Reply Helper */
static void latLongToGeojsonAndReply(redisClient *c, struct geojsonPoint *gp,
                                     char *units) {
    sds geojson = geojsonLatLongToPointFeature(
        gp->latitude, gp->longitude, gp->set, gp->member, gp->dist, units);

    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
    sdsfree(geojson);
}

/* Output Reply Helper */
static void decodeGeohashToGeojsonBoundsAndReply(redisClient *c,
                                                 uint64_t hashbits,
                                                 struct geojsonPoint *gp) {
    GeoHashArea area = {{0,0},{0,0},{0,0}};
    GeoHashBits hash = { .bits = hashbits, .step = GEO_STEP_MAX };

    geohashDecodeWGS84(hash, &area);

    sds geojson = geojsonBoxToPolygonFeature(
        area.latitude.min, area.longitude.min, area.latitude.max,
        area.longitude.max, gp->set, gp->member);
    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
    sdsfree(geojson);
}

/* The defailt addReplyDouble has too much accuracy.  We use this
 * for returning location distances. "5.21 meters away" is nicer
 * than "5.2144992818115 meters away." */
static inline void addReplyDoubleNicer(redisClient *c, double d) {
    char dbuf[128] = { 0 };
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.2f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
}

/* Output Reply Helper */
static void replyGeojsonCollection(redisClient *c, struct geojsonPoint *gp,
                                   long result_length, char *units) {
    sds geojson = geojsonFeatureCollection(gp, result_length, units);
    addReplyBulkCBuffer(c, geojson, sdslen(geojson));
    sdsfree(geojson);
}

/* geohash range+zset access helper */
/* Obtain all members between the min/max of this geohash bounding box. */
/* Returns list of results.  List must be listRelease()'d later. */
