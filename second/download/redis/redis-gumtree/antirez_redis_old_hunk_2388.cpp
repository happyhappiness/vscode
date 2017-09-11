            }
            freeMemoryIfNeeded();
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"hz")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.hz = (int) ll;
        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-policy")) {
