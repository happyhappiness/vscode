void
ipcacheCycleAddr(const char *name, ipcache_addrs * ia)
{
    ipcache_entry *i;
    unsigned char k;
    assert(name || ia);

    if (NULL == ia) {
        if ((i = ipcache_get(name)) == NULL)
            return;

        if (i->flags.negcached)
            return;

        ia = &i->addrs;
    }

    for (k = 0; k < ia->count; ++k) {
        if (++ia->cur == ia->count)
            ia->cur = 0;

        if (!ia->bad_mask[ia->cur])
            break;
    }

    if (k == ia->count) {
        /* All bad, reset to All good */
        debugs(14, 3, "ipcacheCycleAddr: Changing ALL " << name << " addrs from BAD to OK");

        for (k = 0; k < ia->count; ++k)
            ia->bad_mask[k] = 0;

        ia->badcount = 0;

        ia->cur = 0;
    }

    /* NP: zero-based so we increase the human-readable number of our position */
    debugs(14, 3, "ipcacheCycleAddr: " << name << " now at " << ia->in_addrs[ia->cur] << " (" << (ia->cur+1) << " of " << ia->count << ")");
}