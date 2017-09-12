static list *membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double x,
                                   double y, double radius) {
    list *l = NULL;
    GeoHashBits neighbors[9];
    unsigned int i;

    neighbors[0] = n.hash;
    neighbors[1] = n.neighbors.north;
    neighbors[2] = n.neighbors.south;
    neighbors[3] = n.neighbors.east;
    neighbors[4] = n.neighbors.west;
    neighbors[5] = n.neighbors.north_east;
    neighbors[6] = n.neighbors.north_west;
    neighbors[7] = n.neighbors.south_east;
    neighbors[8] = n.neighbors.south_west;

    /* For each neighbor (*and* our own hashbox), get all the matching
     * members and add them to the potential result list. */
    for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
        list *r;

        if (HASHISZERO(neighbors[i]))
            continue;

        r = membersOfGeoHashBox(zobj, neighbors[i]);
        if (!r)
            continue;

        if (!l) {
            l = r;
        } else {
            listJoin(l, r);
        }
    }

    /* if no results across any neighbors (*and* ourself, which is unlikely),
     * then just give up. */
    if (!l)
        return NULL;

    /* Iterate over all matching results in the combined 9-grid search area */
    /* Remove any results outside of our search radius. */
    listIter li;
    listNode *ln;
    listRewind(l, &li);
    while ((ln = listNext(&li))) {
        struct zipresult *zr = listNodeValue(ln);
        GeoHashArea area = {{0,0},{0,0},{0,0}};
        GeoHashBits hash = { .bits = (uint64_t)zr->score,
                             .step = GEO_STEP_MAX };

        if (!geohashDecodeWGS84(hash, &area)) {
            /* Perhaps we should delete this node if the decode fails? */
            continue;
        }

        double neighbor_y = (area.latitude.min + area.latitude.max) / 2;
        double neighbor_x = (area.longitude.min + area.longitude.max) / 2;

        double distance;
        if (!geohashGetDistanceIfInRadiusWGS84(x, y, neighbor_x, neighbor_y,
                                               radius, &distance)) {
            /* If result is in the grid, but not in our radius, remove it. */
            listDelNode(l, ln);
#ifdef DEBUG
            fprintf(stderr, "No match for neighbor (%f, %f) within (%f, %f) at "
                            "distance %f\n",
                    neighbor_y, neighbor_x, y, x, distance);
#endif
        } else {
/* Else: bueno. */
#ifdef DEBUG
            fprintf(
                stderr,
                "Matched neighbor (%f, %f) within (%f, %f) at distance %f\n",
                neighbor_y, neighbor_x, y, x, distance);
#endif
            zr->distance = distance;
        }
    }

    /* We found results, but rejected all of them as out of range. Clean up. */
    if (!listLength(l)) {
        listRelease(l);
        l = NULL;
    }

    /* Success! */
    return l;
}