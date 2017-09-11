        return;
    }

    redisClient *client = c;
    int elements = (c->argc - 2) / 3;
    /* elements will always be correct size (integer math floors for us if we
     * have 6 or 7 total arguments) */
    if (elements > 1) {
        /* We should probably use a static client and not create/free it
         * for every multi-add */
        client = createClient(-1); /* fake client for multi-zadd */

        /* Tell fake client to use the same DB as our calling client. */
        selectDb(client, c->db->id);
    }

    /* Capture all lat/long components up front so if we encounter an error we
     * return before making any changes to the database. */
    double latlong[elements * 2];
    for (int i = 0; i < elements; i++) {
        if (!extractLatLongOrReply(c, (c->argv + 2) + (i * 3),
                                   latlong + (i * 2)))
            return;
    }

    /* Add all (lat, long, value) triples to the requested zset */
    for (int i = 0; i < elements; i++) {
        uint8_t step = geohashEstimateStepsByRadius(radius_meters);

#ifdef DEBUG
        printf("Adding with step size: %d\n", step);
#endif
        GeoHashBits hash;
        int ll_offset = i * 2;
        double latitude = latlong[ll_offset];
        double longitude = latlong[ll_offset + 1];
        geohashEncodeWGS84(latitude, longitude, step, &hash);

        GeoHashFix52Bits bits = geohashAlign52Bits(hash);
        robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
        robj *val = c->argv[2 + i * 3 + 2];
        /* (base args) + (offset for this triple) + (offset of value arg) */

        rewriteClientCommandVector(client, 4, cmd, key, score, val);
        decrRefCount(score);
        zaddCommand(client);
    }

    /* If we used a fake client, return a real reply then free fake client. */
    if (client != c) {
        addReplyLongLong(c, elements);
        freeClient(client);
    }
}

#define SORT_NONE 0
