 * than "5.2144992818115 meters away." We provide 4 digits after the dot
 * so that the returned value is decently accurate even when the unit is
 * the kilometer. */
static inline void addReplyDoubleDistance(redisClient *c, double d) {
    char dbuf[128];
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
