static void
external_acl_cache_touch(external_acl * def, const ExternalACLEntryPointer &entry)
{
    // this must not be done when nothing is being cached.
    if (def->cache_size <= 0 || (def->ttl <= 0 && entry->result == 1) || (def->negative_ttl <= 0 && entry->result != 1))
        return;

    dlinkDelete(&entry->lru, &def->lru_list);
    ExternalACLEntry *e = const_cast<ExternalACLEntry *>(entry.getRaw()); // XXX: make hash a std::map of Pointer.
    dlinkAdd(e, &entry->lru, &def->lru_list);
}