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
