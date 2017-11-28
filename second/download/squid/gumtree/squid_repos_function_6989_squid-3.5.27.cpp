void
Ipc::StoreMapAnchor::set(const StoreEntry &from)
{
    assert(writing() && !reading());
    memcpy(key, from.key, sizeof(key));
    basics.timestamp = from.timestamp;
    basics.lastref = from.lastref;
    basics.expires = from.expires;
    basics.lastmod = from.lastModified();
    basics.swap_file_sz = from.swap_file_sz;
    basics.refcount = from.refcount;
    basics.flags = from.flags;
}