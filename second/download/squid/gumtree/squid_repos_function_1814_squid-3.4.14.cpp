void
external_acl::add(const ExternalACLEntryPointer &anEntry)
{
    trimCache();
    assert(anEntry != NULL);
    assert (anEntry->def == NULL);
    anEntry->def = this;
    ExternalACLEntry *e = const_cast<ExternalACLEntry *>(anEntry.getRaw()); // XXX: make hash a std::map of Pointer.
    hash_join(cache, e);
    dlinkAdd(e, &e->lru, &lru_list);
    e->lock(); //cbdataReference(e); // lock it on behalf of the hash
    ++cache_entries;
}