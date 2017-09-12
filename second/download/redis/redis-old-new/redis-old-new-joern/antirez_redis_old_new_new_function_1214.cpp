void geoAddCommand(redisClient *c) {
    /* args 0-4: [cmd, key, lng, lat, val]; optional 5-6: [radius, units]
     * - OR -
     * args 0-N: [cmd, key, lng, lat, val, lng2, lat2, val2, ...] */

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

    int elements = (c->argc - 2) / 3;
    int argc = 2+elements*2; /* ZADD key score ele ... */
    robj **argv = zcalloc(argc*sizeof(robj*));
    argv[0] = createRawStringObject("zadd",4);
    argv[1] = c->argv[1]; /* key */
    incrRefCount(argv[1]);

    /* Create the argument vector to call ZADD in order to add all
     * the score,value pairs to the requested zset, where score is actually
     * an encoded version of lat,long. */
    uint8_t step = geohashEstimateStepsByRadius(radius_meters,0);
    int i;
    for (i = 0; i < elements; i++) {
        double xy[2];

        if (extractLongLatOrReply(c, (c->argv+2)+(i*3),xy) == REDIS_ERR) {
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
        geohashEncodeWGS84(xy[0], xy[1], step, &hash);
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