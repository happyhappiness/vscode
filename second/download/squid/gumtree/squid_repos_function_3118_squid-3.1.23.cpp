static int
fqdncacheExpiredEntry(const fqdncache_entry * f)
{
    /* all static entries are locked, so this takes care of them too */

    if (f->locks != 0)
        return 0;

    if (f->expires > squid_curtime)
        return 0;

    return 1;
}