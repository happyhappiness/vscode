bool ReadRecord(StoreSwapLogData &swapData) {
        assert(log);
        return fread(&swapData, sizeof(StoreSwapLogData), 1, log) == 1;
    }