                        DumpWrapper, 0, 1);
}

void
PconnModule::add(PconnPool *aPool)
{
    pools.insert(aPool);
}

void
PconnModule::remove(PconnPool *aPool)
{
    pools.erase(aPool);
}

void
PconnModule::dump(StoreEntry *e)
{
    typedef Pools::const_iterator PCI;
    int i = 0; // TODO: Why number pools if they all have names?
    for (PCI p = pools.begin(); p != pools.end(); ++p, ++i) {
        // TODO: Let each pool dump itself the way it wants to.
        storeAppendPrintf(e, "\n Pool %d Stats\n", i);
        (*p)->dumpHist(e);
        storeAppendPrintf(e, "\n Pool %d Hash Table\n",i);
        (*p)->dumpHash(e);
    }
}

void
PconnModule::DumpWrapper(StoreEntry *e)
{
