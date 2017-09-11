}

/* The defailt addReplyDouble has too much accuracy.  We use this
 * for returning location distances. "5.21 meters away" is nicer
 * than "5.2144992818115 meters away." */
static inline void addReplyDoubleMeters(redisClient *c, double d) {
    char dbuf[128] = { 0 };
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.2f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
}

