void
ipcacheInvalidateNegative(const char *name)
{
    ipcache_entry *i;

    if ((i = ipcache_get(name)) == NULL)
        return;

    if (i->flags.negcached)
        i->expires = squid_curtime;

    /*
     * NOTE, don't call ipcacheRelease here because we might be here due
     * to a thread started from a callback.
     */
}