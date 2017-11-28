void
ipcacheMarkGoodAddr(const char *name, const Ip::Address &addr)
{
    ipcache_entry *i;
    ipcache_addrs *ia;
    int k;

    if ((i = ipcache_get(name)) == NULL)
        return;

    ia = &i->addrs;

    for (k = 0; k < (int) ia->count; ++k) {
        if (addr == ia->in_addrs[k])
            break;
    }

    if (k == (int) ia->count)   /* not found */
        return;

    if (!ia->bad_mask[k])   /* already OK */
        return;

    ia->bad_mask[k] = FALSE;

    -- ia->badcount;

    debugs(14, 2, "ipcacheMarkGoodAddr: " << name << " " << addr );
}