int
ipcacheAddEntryFromHosts(const char *name, const char *ipaddr)
{
    ipcache_entry *i;

    IpAddress ip;

    if (!(ip = ipaddr)) {
        if (strchr(ipaddr, ':') && strspn(ipaddr, "0123456789abcdefABCDEF:") == strlen(ipaddr)) {
            debugs(14, 3, "ipcacheAddEntryFromHosts: Skipping IPv6 address '" << ipaddr << "'");
        } else {
            debugs(14, 1, "ipcacheAddEntryFromHosts: Bad IP address '" << ipaddr << "'");
        }

        return 1;
    }

    if ((i = ipcache_get(name))) {
        if (1 == i->flags.fromhosts) {
            ipcacheUnlockEntry(i);
        } else if (i->locks > 0) {
            debugs(14, 1, "ipcacheAddEntryFromHosts: can't add static entry for locked name '" << name << "'");
            return 1;
        } else {
            ipcacheRelease(i);
        }
    }

    i = ipcacheCreateEntry(name);
    i->addrs.count = 1;
    i->addrs.cur = 0;
    i->addrs.badcount = 0;

    i->addrs.in_addrs = (IpAddress *)xcalloc(1, sizeof(IpAddress));
    i->addrs.bad_mask = (unsigned char *)xcalloc(1, sizeof(unsigned char));
    i->addrs.in_addrs[0] = ip;
    i->addrs.bad_mask[0] = FALSE;
    i->flags.fromhosts = 1;
    ipcacheAddEntry(i);
    ipcacheLockEntry(i);
    return 0;
}