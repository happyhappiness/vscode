void
Adaptation::Config::DumpServiceGroups(StoreEntry *entry, const char *name)
{
    typedef Groups::iterator GI;
    for (GI i = AllGroups().begin(); i != AllGroups().end(); ++i)
        storeAppendPrintf(entry, "%s " SQUIDSTRINGPH "\n", name, SQUIDSTRINGPRINT((*i)->id));
}