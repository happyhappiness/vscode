void
PconnModule::dump(StoreEntry *e)
{
    int i;

    for (i = 0; i < poolCount; i++) {
        storeAppendPrintf(e, "\n Pool %d Stats\n", i);
        (*(pools+i))->dumpHist(e);
        storeAppendPrintf(e, "\n Pool %d Hash Table\n",i);
        (*(pools+i))->dumpHash(e);
    }
}