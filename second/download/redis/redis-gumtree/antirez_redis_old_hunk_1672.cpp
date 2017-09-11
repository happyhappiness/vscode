    } else {
        redisPanic("Unknown type");
    }
    redisAssertWithInfo(c,sortval,j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
