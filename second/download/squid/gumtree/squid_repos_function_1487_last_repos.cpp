void
external_acl::trimCache()
{
    if (cache_size && cache_entries >= cache_size) {
        ExternalACLEntryPointer e(static_cast<ExternalACLEntry *>(lru_list.tail->data));
        external_acl_cache_delete(this, e);
    }
}