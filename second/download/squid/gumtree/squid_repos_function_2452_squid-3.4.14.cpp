static int
ipcacheExpiredEntry(ipcache_entry * i)
{
    /* all static entries are locked, so this takes care of them too */

    if (i->locks != 0)
        return 0;

    if (i->addrs.count == 0)
        if (0 == i->flags.negcached)
            return 1;

    if (i->expires > squid_curtime)
        return 0;

    return 1;
}