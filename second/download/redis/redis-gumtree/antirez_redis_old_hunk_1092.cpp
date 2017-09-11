
/* Input Argument Helper */
/* Take a pointer to the latitude arg then use the next arg for longitude.
 * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
int extractLongLatOrReply(client *c, robj **argv,
                                        double *xy) {
    for (int i = 0; i < 2; i++) {
        if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
            REDIS_OK) {
            return REDIS_ERR;
        }
        if (xy[0] < GEO_LONG_MIN || xy[0] > GEO_LONG_MAX ||
            xy[1] < GEO_LAT_MIN  || xy[1] > GEO_LAT_MAX) {
            addReplySds(c, sdscatprintf(sdsempty(),
                "-ERR invalid longitude,latitude pair %f,%f\r\n",xy[0],xy[1]));
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}

/* Input Argument Helper */
/* Decode lat/long from a zset member's score.
 * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
int longLatFromMember(robj *zobj, robj *member, double *xy) {
    double score = 0;

    if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
    if (!decodeGeohash(score, xy)) return REDIS_ERR;
    return REDIS_OK;
}

/* Check that the unit argument matches one of the known units, and returns
