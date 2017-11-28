void
StoreEntry::dump(int l) const
{
    debugs(20, l, "StoreEntry->key: " << getMD5Text());
    debugs(20, l, "StoreEntry->next: " << next);
    debugs(20, l, "StoreEntry->mem_obj: " << mem_obj);
    debugs(20, l, "StoreEntry->timestamp: " << timestamp);
    debugs(20, l, "StoreEntry->lastref: " << lastref);
    debugs(20, l, "StoreEntry->expires: " << expires);
    debugs(20, l, "StoreEntry->lastModified_: " << lastModified_);
    debugs(20, l, "StoreEntry->swap_file_sz: " << swap_file_sz);
    debugs(20, l, "StoreEntry->refcount: " << refcount);
    debugs(20, l, "StoreEntry->flags: " << storeEntryFlags(this));
    debugs(20, l, "StoreEntry->swap_dirn: " << swap_dirn);
    debugs(20, l, "StoreEntry->swap_filen: " << swap_filen);
    debugs(20, l, "StoreEntry->lock_count: " << lock_count);
    debugs(20, l, "StoreEntry->mem_status: " << mem_status);
    debugs(20, l, "StoreEntry->ping_status: " << ping_status);
    debugs(20, l, "StoreEntry->store_status: " << store_status);
    debugs(20, l, "StoreEntry->swap_status: " << swap_status);
}