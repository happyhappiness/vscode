void
external_acl::trimCache()
{
    if (cache_size && cache_entries >= cache_size)
        external_acl_cache_delete(this, static_cast<external_acl_entry *>(lru_list.tail->data));
}