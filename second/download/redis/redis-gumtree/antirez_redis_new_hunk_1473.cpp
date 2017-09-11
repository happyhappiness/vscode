        return;
    }

    int elements = (c->argc - 2) / 3;
    int argc = 2+elements*2; /* ZADD key score ele ... */
    robj **argv = zcalloc(argc*sizeof(robj*));
    argv[0] = createRawStringObject("zadd",4);
    argv[1] = c->argv[1]; /* key */
    incrRefCount(argv[1]);

    /* Create the argument vector to call ZADD in order to add all
     * the score,value pairs to the requested zset, where score is actually
     * an encoded version of lat,long. */
    uint8_t step = geohashEstimateStepsByRadius(radius_meters);
    int i;
    for (i = 0; i < elements; i++) {
        double latlong[elements * 2];

        if (!extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong)) {
            for (i = 0; i < argc; i++)
                if (argv[i]) decrRefCount(argv[i]);
            zfree(argv);
            return;
        }

#ifdef DEBUG
        printf("Adding with step size: %d\n", step);
#endif

        /* Turn the coordinates into the score of the element. */
        GeoHashBits hash;
        double latitude = latlong[0];
        double longitude = latlong[1];
        geohashEncodeWGS84(latitude, longitude, step, &hash);

        GeoHashFix52Bits bits = geohashAlign52Bits(hash);
        robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
        robj *val = c->argv[2 + i * 3 + 2];
        argv[2+i*2] = score;
        argv[3+i*2] = val;
        incrRefCount(val);
    }

    /* Finally call ZADD that will do the work for us. */
    replaceClientCommandVector(c,argc,argv);
    zaddCommand(c);
}

#define SORT_NONE 0
