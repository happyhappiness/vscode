static inline void addReplyDoubleMeters(redisClient *c, double d) {
    char dbuf[128] = { 0 };
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.2f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
}