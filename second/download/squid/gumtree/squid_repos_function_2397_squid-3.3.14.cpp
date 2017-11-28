void
ipcacheMarkAllGood(const char *name)
{
    ipcache_entry *i;
    ipcache_addrs *ia;
    int k;

    if ((i = ipcache_get(name)) == NULL)
        return;

    ia = &i->addrs;

    /* All bad, reset to All good */
    debugs(14, 3, "ipcacheMarkAllGood: Changing ALL " << name << " addrs to OK (" << ia->badcount << "/" << ia->count << " bad)");

    for (k = 0; k < ia->count; ++k)
        ia->bad_mask[k] = 0;

    ia->badcount = 0;
}