        }
        dictReleaseIterator(di);
    }
    printf("**************************** %d == %d\n",
        j, vectorlen);
    redisAssert(j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
