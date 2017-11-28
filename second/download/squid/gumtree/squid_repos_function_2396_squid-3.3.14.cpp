void
ipcacheMarkBadAddr(const char *name, const Ip::Address &addr)
{
    ipcache_entry *i;
    ipcache_addrs *ia;
    int k;

    /** Does nothing if the domain name does not exist. */
    if ((i = ipcache_get(name)) == NULL)
        return;

    ia = &i->addrs;

    for (k = 0; k < (int) ia->count; ++k) {
        if (addr == ia->in_addrs[k] )
            break;
    }

    /** Does nothing if the IP does not exist for the doamin. */
    if (k == (int) ia->count)
        return;

    /** Marks the given address as BAD */
    if (!ia->bad_mask[k]) {
        ia->bad_mask[k] = TRUE;
        ++ia->badcount;
        i->expires = min(squid_curtime + max((time_t)60, Config.negativeDnsTtl), i->expires);
        debugs(14, 2, "ipcacheMarkBadAddr: " << name << " " << addr );
    }

    /** then calls ipcacheCycleAddr() to advance the current pointer to the next OK address. */
    ipcacheCycleAddr(name, ia);
}