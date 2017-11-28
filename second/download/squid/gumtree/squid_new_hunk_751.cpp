        }
    }
}

void ClientDelayConfig::freePoolCount()
{
    pools.clear();
}

void ClientDelayConfig::dumpPoolCount(StoreEntry * entry, const char *name) const
{
    if (pools.size()) {
        storeAppendPrintf(entry, "%s %d\n", name, (int)pools.size());
