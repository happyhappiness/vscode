static void
fvdbDumpTable(StoreEntry * e, hash_table * hash)
{
    hash_link *h;
    fvdb_entry *fv;

    if (hash == NULL)
        return;

    hash_first(hash);

    while ((h = hash_next(hash))) {
        fv = (fvdb_entry *) h;
        storeAppendPrintf(e, "%9d %s\n", fv->n, hashKeyStr(&fv->hash));
    }
}