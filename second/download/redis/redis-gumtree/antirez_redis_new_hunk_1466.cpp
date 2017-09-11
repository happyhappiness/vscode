
/* GEOADD key long lat name [long2 lat2 name2 ... longN latN nameN] */
void geoAddCommand(redisClient *c) {
    /* Check arguments number for sanity. */
    if ((c->argc - 2) % 3 != 0) {
        /* Need an odd number of arguments if we got this far... */
        addReplyError(c, "syntax error. Try GEOADD key [x1] [y1] [name1] "
                         "[x2] [y2] [name2] ... ");
        return;
    }

