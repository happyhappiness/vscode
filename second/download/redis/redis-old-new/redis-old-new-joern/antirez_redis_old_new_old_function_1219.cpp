static void geoRadiusGeneric(redisClient *c, int type) {
    /* type == cords:  [cmd, key, lat, long, radius, units, [optionals]]
     * type == member: [cmd, key, member,    radius, units, [optionals]] */
    robj *key = c->argv[1];

    /* Look up the requested zset */
    robj *zobj = NULL;
    if ((zobj = lookupKeyReadOrReply(c, key, shared.emptymultibulk)) == NULL ||
        checkType(c, zobj, REDIS_ZSET)) {
        return;
    }

    /* Find lat/long to use for radius search based on inquiry type */
    int base_args;
    double latlong[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (!extractLatLongOrReply(c, c->argv + 2, latlong))
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (!latLongFromMember(zobj, member, latlong)) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
    } else {
        addReplyError(c, "unknown georadius search type");
        return;
    }

    /* Extract radius and units from arguments */
    double radius_meters = 0, conversion = 1;
    if ((radius_meters = extractDistanceOrReply(c, c->argv + base_args - 2,
                                                &conversion)) < 0) {
        return;
    }

    sds units = c->argv[base_args - 2 + 1]->ptr;

    /* Discover and populate all optional parameters. */
    int withdist = 0, withhash = 0, withcoords = 0,
         withgeojson = 0, withgeojsonbounds = 0,
         withgeojsoncollection = 0, noproperties = 0;
    int sort = SORT_NONE;
    if (c->argc > base_args) {
        int remaining = c->argc - base_args;
        for (int i = 0; i < remaining; i++) {
            char *arg = c->argv[base_args + i]->ptr;
            if (!strncasecmp(arg, "withdist", 8))
                withdist = 1;
            else if (!strcasecmp(arg, "withhash"))
                withhash = 1;
            else if (!strncasecmp(arg, "withcoord", 9))
                withcoords = 1;
            else if (!strncasecmp(arg, "withgeojsonbound", 16))
                withgeojsonbounds = 1;
            else if (!strncasecmp(arg, "withgeojsoncollection", 21))
                withgeojsoncollection = 1;
            else if (!strncasecmp(arg, "withgeo", 7) ||
                     !strcasecmp(arg, "geojson") || !strcasecmp(arg, "json") ||
                     !strcasecmp(arg, "withjson"))
                withgeojson = 1;
            else if (!strncasecmp(arg, "noprop", 6) ||
                     !strncasecmp(arg, "withoutprop", 11))
                noproperties = 1;
            else if (!strncasecmp(arg, "asc", 3) ||
                     !strncasecmp(arg, "sort", 4))
                sort = SORT_ASC;
            else if (!strncasecmp(arg, "desc", 4))
                sort = SORT_DESC;
            else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    int withgeo = withgeojsonbounds || withgeojsoncollection || withgeojson;

    /* Get all neighbor geohash boxes for our radius search */
    GeoHashRadius georadius =
        geohashGetAreasByRadiusWGS84(latlong[0], latlong[1], radius_meters);

#ifdef DEBUG
    printf("Searching with step size: %d\n", georadius.hash.step);
#endif
    /* {Lat, Long} = {y, x} */
    double y = latlong[0];
    double x = latlong[1];

    /* Search the zset for all matching points */
    list *found_matches =
        membersOfAllNeighbors(zobj, georadius, x, y, radius_meters);

    /* If no matching results, the user gets an empty reply. */
    if (!found_matches) {
        addReply(c, shared.emptymultibulk);
        return;
    }

    long result_length = listLength(found_matches);
    long option_length = 0;

    /* Our options are self-contained nested multibulk replies, so we
     * only need to track how many of those nested replies we return. */
    if (withdist)
        option_length++;

    if (withcoords)
        option_length++;

    if (withhash)
        option_length++;

    if (withgeojson)
        option_length++;

    if (withgeojsonbounds)
        option_length++;

    /* The multibulk len we send is exactly result_length. The result is either
     * all strings of just zset members  *or* a nested multi-bulk reply
     * containing the zset member string _and_ all the additional options the
     * user enabled for this request. */
    addReplyMultiBulkLen(c, result_length + withgeojsoncollection);

    /* Iterate over results, populate struct used for sorting and result sending
     */
    listIter li;
    listRewind(found_matches, &li);
    struct geojsonPoint gp[result_length];
    /* populate gp array from our results */
    for (int i = 0; i < result_length; i++) {
        struct zipresult *zr = listNodeValue(listNext(&li));

        gp[i].member = NULL;
        gp[i].set = key->ptr;
        gp[i].dist = zr->distance / conversion;
        gp[i].userdata = zr;

        /* The layout of geojsonPoint allows us to pass the start offset
         * of the struct directly to decodeGeohash. */
        decodeGeohash(zr->score, (double *)(gp + i));
    }

    /* Process [optional] requested sorting */
    if (sort == SORT_ASC) {
        qsort(gp, result_length, sizeof(*gp), sort_gp_asc);
    } else if (sort == SORT_DESC) {
        qsort(gp, result_length, sizeof(*gp), sort_gp_desc);
    }

    /* Finally send results back to the caller */
    for (int i = 0; i < result_length; i++) {
        struct zipresult *zr = gp[i].userdata;

        /* If we have options in option_length, return each sub-result
         * as a nested multi-bulk.  Add 1 to account for result value itself. */
        if (option_length)
            addReplyMultiBulkLen(c, option_length + 1);

        switch (zr->type) {
        case ZR_LONG:
            addReplyBulkLongLong(c, zr->val.v);
            if (withgeo && !noproperties)
                gp[i].member = sdscatprintf(sdsempty(), "%llu", zr->val.v);
            break;
        case ZR_STRING:
            addReplyBulkCBuffer(c, zr->val.s, sdslen(zr->val.s));
            if (withgeo && !noproperties)
                gp[i].member = sdsdup(zr->val.s);
            break;
        }

        if (withdist)
            addReplyDoubleNicer(c, gp[i].dist);

        if (withhash)
            addReplyLongLong(c, zr->score);

        if (withcoords) {
            addReplyMultiBulkLen(c, 2);
            addReplyDouble(c, gp[i].latitude);
            addReplyDouble(c, gp[i].longitude);
        }

        if (withgeojson)
            latLongToGeojsonAndReply(c, gp + i, units);

        if (withgeojsonbounds)
            decodeGeohashToGeojsonBoundsAndReply(c, zr->score, gp + i);
    }

    if (withgeojsoncollection)
        replyGeojsonCollection(c, gp, result_length, units);

    if (withgeo && !noproperties)
        for (int i = 0; i < result_length; i++)
            sdsfree(gp[i].member);

    listRelease(found_matches);
}