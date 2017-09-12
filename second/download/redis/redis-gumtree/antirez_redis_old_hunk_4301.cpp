        }
        dictReleaseIterator(di);
    }
    redisAssert(j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
