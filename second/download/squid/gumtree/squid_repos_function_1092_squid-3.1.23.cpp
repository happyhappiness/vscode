static void
dump_refreshpattern(StoreEntry * entry, const char *name, refresh_t * head)
{
    while (head != NULL) {
        storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                          name,
                          head->flags.icase ? " -i" : null_string,
                          head->pattern,
                          (int) head->min / 60,
                          (int) (100.0 * head->pct + 0.5),
                          (int) head->max / 60);

        if (head->flags.refresh_ims)
            storeAppendPrintf(entry, " refresh-ims");

#if HTTP_VIOLATIONS

        if (head->flags.override_expire)
            storeAppendPrintf(entry, " override-expire");

        if (head->flags.override_lastmod)
            storeAppendPrintf(entry, " override-lastmod");

        if (head->flags.reload_into_ims)
            storeAppendPrintf(entry, " reload-into-ims");

        if (head->flags.ignore_reload)
            storeAppendPrintf(entry, " ignore-reload");

        if (head->flags.ignore_no_cache)
            storeAppendPrintf(entry, " ignore-no-cache");

        if (head->flags.ignore_no_store)
            storeAppendPrintf(entry, " ignore-no-store");

        if (head->flags.ignore_must_revalidate)
            storeAppendPrintf(entry, " ignore-must-revalidate");

        if (head->flags.ignore_private)
            storeAppendPrintf(entry, " ignore-private");

        if (head->flags.ignore_auth)
            storeAppendPrintf(entry, " ignore-auth");

#endif

        storeAppendPrintf(entry, "\n");

        head = head->next;
    }
}