static void
external_acl_cache_delete(external_acl * def, const ExternalACLEntryPointer &entry)
{
    assert(entry != NULL);
    assert(def->cache_size > 0 && entry->def == def);
    ExternalACLEntry *e = const_cast<ExternalACLEntry *>(entry.getRaw()); // XXX: make hash a std::map of Pointer.
    hash_remove_link(def->cache, e);
    dlinkDelete(&e->lru, &def->lru_list);
    e->unlock(); // unlock on behalf of the hash
    def->cache_entries -= 1;
}