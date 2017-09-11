#ifdef DEBUG
    printf("Searching with step size: %d\n", georadius.hash.step);
#endif
    /* {Lat, Long} = {y, x} */
    double y = latlong[0];
    double x = latlong[1];

    /* Search the zset for all matching points */
    geoArray *ga = geoArrayCreate();
    membersOfAllNeighbors(zobj, georadius, x, y, radius_meters, ga);

    /* If no matching results, the user gets an empty reply. */
    if (ga->used == 0) {
