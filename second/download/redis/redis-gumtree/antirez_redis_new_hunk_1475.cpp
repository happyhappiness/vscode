    /* For each neighbor (*and* our own hashbox), get all the matching
     * members and add them to the potential result list. */
    for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
        if (HASHISZERO(neighbors[i]))
            continue;
        count += membersOfGeoHashBox(zobj, neighbors[i], ga, x, y, radius);
    }
    return count;
}

/* Sort comparators for qsort() */
