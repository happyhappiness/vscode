double extractUnitOrReply(redisClient *c, robj *unit) {
    char *u = unit->ptr;

    if (!strcmp(u, "m")) {
        return 1;
    } else if (!strcmp(u, "km")) {
        return 1000;
    } else if (!strcmp(u, "ft")) {
        return 0.3048;
    } else if (!strcmp(u, "mi")) {
        return 1609.34;
    } else {
        addReplyError(c,
            "unsupported unit provided. please use m, km, ft, mi");
        return -1;
    }
}
