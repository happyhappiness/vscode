void
DelayPool::dump(StoreEntry *entry, unsigned int i) const
{
    if (theComposite() == NULL)
        return;

    storeAppendPrintf(entry, "delay_class %d %s\n", i + 1, pool->theClassTypeLabel());

    LOCAL_ARRAY(char, nom, 32);

    snprintf(nom, 32, "delay_access %d", i + 1);

    dump_acl_access(entry, nom, access);

    storeAppendPrintf(entry, "delay_parameters %d", i + 1);

    theComposite()->dump (entry);

    storeAppendPrintf(entry, "\n");
}