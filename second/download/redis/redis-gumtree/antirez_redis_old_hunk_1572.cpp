    } else {
        redisPanic("Unknown type");
    }
    printf("j: %d; vectorlen: %d\n", j, vectorlen);
    redisAssertWithInfo(c,sortval,j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
