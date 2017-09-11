    curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;

    if (sender == myself) {
        serverLog(REDIS_WARNING,"Discarding UPDATE message about myself.");
        return;
    }

