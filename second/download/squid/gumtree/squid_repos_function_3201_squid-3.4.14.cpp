static void
fqdncacheRelease(fqdncache_entry * f)
{
    int k;
    hash_remove_link(fqdn_table, (hash_link *) f);

    for (k = 0; k < (int) f->name_count; ++k)
        safe_free(f->names[k]);

    debugs(35, 5, "fqdncacheRelease: Released FQDN record for '" << hashKeyStr(&f->hash) << "'.");

    dlinkDelete(&f->lru, &lru_list);

    safe_free(f->hash.key);

    safe_free(f->error_message);

    memFree(f, MEM_FQDNCACHE_ENTRY);
}