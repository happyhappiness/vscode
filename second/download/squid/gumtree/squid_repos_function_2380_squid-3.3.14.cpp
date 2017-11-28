static ipcache_entry *
ipcacheCreateEntry(const char *name)
{
    static ipcache_entry *i;
    i = (ipcache_entry *)memAllocate(MEM_IPCACHE_ENTRY);
    i->hash.key = xstrdup(name);
    Tolower(static_cast<char*>(i->hash.key));
    i->expires = squid_curtime + Config.negativeDnsTtl;
    return i;
}