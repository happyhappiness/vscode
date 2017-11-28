static void
fvdbCount(hash_table * hash, const char *key)
{
    fvdb_entry *fv;

    if (NULL == hash)
        return;

    fv = (fvdb_entry *)hash_lookup(hash, key);

    if (NULL == fv) {
        fv = static_cast <fvdb_entry *>(xcalloc(1, sizeof(fvdb_entry)));
        fv->hash.key = xstrdup(key);
        hash_join(hash, &fv->hash);
    }

    ++ fv->n;
}