int
ipcacheAddEntryFromHosts(const char *name, const char *ipaddr)
{
    ipcache_entry *i;

    Ip::Address ip;

    if (!(ip = ipaddr)) {
        if (strchr(ipaddr, ':') && strspn(ipaddr, "0123456789abcdefABCDEF:") == strlen(ipaddr)) {
            debugs(14, 3, "ipcacheAddEntryFromHosts: Skipping IPv6 address '" << ipaddr << "'");
        } else {
            debugs(14, DBG_IMPORTANT, "ipcacheAddEntryFromHosts: Bad IP address '" << ipaddr << "'");
        }

        return 1;
    }

    if ((i = ipcache_get(name))) {
        if (1 == i->flags.fromhosts) {
            ipcacheUnlockEntry(i);
        } else if (i->locks > 0) {
            debugs(14, DBG_IMPORTANT, "ipcacheAddEntryFromHosts: can't add static entry for locked name '" << name << "'");
            return 1;
        } else {
            ipcacheRelease(i);
        }
    }

    i = ipcacheCreateEntry(name);
    i->addrs.count = 1;
    i->addrs.cur = 0;
    i->addrs.badcount = 0;

    i->addrs.in_addrs = static_cast<Ip::Address *>(xcalloc(1, sizeof(Ip::Address)));
    i->addrs.bad_mask = (unsigned char *)xcalloc(1, sizeof(unsigned char));
    i->addrs.in_addrs[0] = ip;
    i->addrs.bad_mask[0] = FALSE;
    i->flags.fromhosts = true;
    ipcacheAddEntry(i);
    ipcacheLockEntry(i);
    return 0;
}