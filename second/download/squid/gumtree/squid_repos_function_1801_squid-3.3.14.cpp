void
external_acl::add(ExternalACLEntry *anEntry)
{
    trimCache();
    assert (anEntry->def == NULL);
    anEntry->def = this;
    hash_join(cache, anEntry);
    dlinkAdd(anEntry, &anEntry->lru, &lru_list);
    ++cache_entries;
}