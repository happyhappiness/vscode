bool ReadRecord(StoreSwapLogData &swapData) {
        UFSSwapLogParser_v1_32bs::StoreSwapLogDataOld readData;
        int bytes = sizeof(UFSSwapLogParser_v1_32bs::StoreSwapLogDataOld);

        assert(log);

        if (fread(&readData, bytes, 1, log) != 1) {
            return false;
        }
        swapData.op = readData.op;
        swapData.swap_filen = readData.swap_filen;
        swapData.timestamp = readData.timestamp;
        swapData.lastref = readData.lastref;
        swapData.expires = readData.expires;
        swapData.lastmod = readData.lastmod;
        swapData.swap_file_sz = readData.swap_file_sz;
        swapData.refcount = readData.refcount;
        swapData.flags = readData.flags;
        memcpy(swapData.key, readData.key, SQUID_MD5_DIGEST_LENGTH);
        return true;
    }