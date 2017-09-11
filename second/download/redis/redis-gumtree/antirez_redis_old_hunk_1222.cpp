    zfree(line);
    fclose(fp);

    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s", myself->name);

    /* Something that should never happen: currentEpoch smaller than
     * the max epoch found in the nodes configuration. However we handle this
