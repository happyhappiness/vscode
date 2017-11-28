void ClientDelayConfig::dumpPoolCount(StoreEntry * entry, const char *name) const
{
    if (pools.size()) {
        storeAppendPrintf(entry, "%s %d\n", name, (int)pools.size());
        for (unsigned int i = 0; i < pools.size(); ++i)
            pools[i].dump(entry, i);
    }
}