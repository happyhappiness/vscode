bool UFSSwapLogParser_v1::ReadRecord(StoreSwapLogData &swapData)
{
    int bytes = sizeof(StoreSwapLogData);

    assert(log);

    if (fread(&swapData, bytes, 1, log) != 1) {
        return false;
    }
    return true;
}