static void
ipcacheUnlockEntry(ipcache_entry * i)
{
    if (i->locks < 1) {
        debugs(14, 1, "WARNING: ipcacheEntry unlocked with no lock! locks=" << i->locks);
        return;
    }

    i->locks--;

    if (ipcacheExpiredEntry(i))
        ipcacheRelease(i);
}