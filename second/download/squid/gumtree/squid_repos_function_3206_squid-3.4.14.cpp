static fqdncache_entry *
fqdncacheCreateEntry(const char *name)
{
    static fqdncache_entry *f;
    f = (fqdncache_entry *)memAllocate(MEM_FQDNCACHE_ENTRY);
    f->hash.key = xstrdup(name);
    f->expires = squid_curtime + Config.negativeDnsTtl;
    return f;
}