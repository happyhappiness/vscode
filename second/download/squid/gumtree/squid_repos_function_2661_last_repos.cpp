static void
fqdncacheRelease(fqdncache_entry * f)
{
    hash_remove_link(fqdn_table, (hash_link *) f);
    debugs(35, 5, "fqdncacheRelease: Released FQDN record for '" << hashKeyStr(&f->hash) << "'.");
    dlinkDelete(&f->lru, &lru_list);
    delete f;
}