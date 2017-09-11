    curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;

    if (sender == myself) {
        serverLog(LL_WARNING,"Discarding UPDATE message about myself.");
        return;
    }

