
    /* Get all neighbor geohash boxes for our radius search */
    GeoHashRadius georadius =
        geohashGetAreasByRadiusWGS84(xy[0], xy[1], radius_meters);

#ifdef DEBUG
    printf("Searching with step size: %d\n", georadius.hash.step);
#endif

    /* Search the zset for all matching points */
    geoArray *ga = geoArrayCreate();
    membersOfAllNeighbors(zobj, georadius, xy[0], xy[1], radius_meters, ga);

    /* If no matching results, the user gets an empty reply. */
    if (ga->used == 0) {
