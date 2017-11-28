void
Ipc::StoreMapSlot::set(const StoreEntry &from)
{
    memcpy(key, from.key, sizeof(key));
    // XXX: header = aHeader;
    basics.timestamp = from.timestamp;
    basics.lastref = from.lastref;
    basics.expires = from.expires;
    basics.lastmod = from.lastmod;
    basics.swap_file_sz = from.swap_file_sz;
    basics.refcount = from.refcount;
    basics.flags = from.flags;
}