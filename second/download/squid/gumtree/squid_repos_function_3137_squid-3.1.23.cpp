void
fqdncacheAddEntryFromHosts(char *addr, wordlist * hostnames)
{
    fqdncache_entry *fce;
    int j = 0;

    if ((fce = fqdncache_get(addr))) {
        if (1 == fce->flags.fromhosts) {
            fqdncacheUnlockEntry(fce);
        } else if (fce->locks > 0) {
            debugs(35, 1, "fqdncacheAddEntryFromHosts: can't add static entry for locked address '" << addr << "'");
            return;
        } else {
            fqdncacheRelease(fce);
        }
    }

    fce = fqdncacheCreateEntry(addr);

    while (hostnames) {
        fce->names[j] = xstrdup(hostnames->key);
        Tolower(fce->names[j]);
        j++;
        hostnames = hostnames->next;

        if (j >= FQDN_MAX_NAMES)
            break;
    }

    fce->name_count = j;
    fce->names[j] = NULL;	/* it's safe */
    fce->flags.fromhosts = 1;
    fqdncacheAddEntry(fce);
    fqdncacheLockEntry(fce);
}