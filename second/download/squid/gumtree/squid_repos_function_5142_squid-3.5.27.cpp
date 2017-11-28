void
Rock::SwapDir::dumpTimeOption(StoreEntry * e) const
{
    if (fileConfig.ioTimeout)
        storeAppendPrintf(e, " swap-timeout=%" PRId64,
                          static_cast<int64_t>(fileConfig.ioTimeout));
}