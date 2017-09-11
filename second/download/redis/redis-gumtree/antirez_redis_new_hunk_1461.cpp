    return REDIS_OK;
}

/* Check that the unit argument matches one of the known units, and returns
 * the conversion factor to meters (you need to divide meters by the conversion
 * factor to convert to the right unit).
 *
 * If the unit is not valid, an error is reported to the client, and a value
 * less than zero is returned. */
double extractUnitOrReply(redisClient *c, robj *unit) {
    char *u = unit->ptr;

    if (!strcmp(u, "m") || !strncmp(u, "meter", 5)) {
        return 1;
    } else if (!strcmp(u, "ft") || !strncmp(u, "feet", 4)) {
        return 0.3048;
    } else if (!strcmp(u, "mi") || !strncmp(u, "mile", 4)) {
        return 1609.34;
    } else if (!strcmp(u, "km") || !strncmp(u, "kilometer", 9)) {
        return 1000;
    } else {
        addReplyError(c, "unsupported unit provided. please use meters (m), "
                         "kilometers (km), miles (mi), or feet (ft)");
        return -1;
    }
}

/* Input Argument Helper.
 * Extract the dinstance from the specified two arguments starting at 'argv'
 * that shouldbe in the form: <number> <unit> and return the dinstance in the
