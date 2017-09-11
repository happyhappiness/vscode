
/* GEOADD key long lat name [long2 lat2 name2 ... longN latN nameN] */
void geoAddCommand(redisClient *c) {
    /* Prepare for the three different forms of the add command. */
    double radius_meters = 0;
    if (c->argc == 7) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 5, NULL)) <
            0) {
            return;
        }
    } else if (c->argc == 6) {
        addReplyError(c, "must provide units when asking for radius encode");
        return;
    } else if ((c->argc - 2) % 3 != 0) {
        /* Need an odd number of arguments if we got this far... */
        addReplyError(c, "format is: geoadd [key] [x1] [y1] [member1] "
                         "[x2] [y2] [member2] ... ");
        return;
    }

