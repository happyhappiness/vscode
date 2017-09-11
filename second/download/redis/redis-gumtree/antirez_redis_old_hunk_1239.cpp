    curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;

    if (sender == myself) {
        redisLog(REDIS_WARNING,"Discarding UPDATE message about myself.");
        return;
    }

