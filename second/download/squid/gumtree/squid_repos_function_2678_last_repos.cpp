void
fqdncacheAddEntryFromHosts(char *addr, SBufList &hostnames)
{
    fqdncache_entry *fce= fqdncache_get(addr);
    if (fce) {
        if (1 == fce->flags.fromhosts) {
            fqdncacheUnlockEntry(fce);
        } else if (fce->locks > 0) {
            debugs(35, DBG_IMPORTANT, "WARNING: can't add static entry for locked address '" << addr << "'");
            return;
        } else {
            fqdncacheRelease(fce);
        }
    }

    fce = new fqdncache_entry(addr);

    int j = 0;
    for (auto &h : hostnames) {
        fce->names[j] = xstrdup(h.c_str());
        Tolower(fce->names[j]);
        ++j;

        if (j >= FQDN_MAX_NAMES)
            break;
    }

    fce->name_count = j;
    fce->names[j] = NULL;   /* it's safe */
    fce->flags.fromhosts = true;
    fqdncacheAddEntry(fce);
    fqdncacheLockEntry(fce);
}