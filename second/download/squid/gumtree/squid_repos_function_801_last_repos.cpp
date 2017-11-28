static void
dump_refreshpattern(StoreEntry * entry, const char *name, RefreshPattern * head)
{
    while (head != NULL) {
        storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                          name,
                          head->pattern.flags&REG_ICASE ? " -i" : null_string,
                          head->pattern.c_str(),
                          (int) head->min / 60,
                          (int) (100.0 * head->pct + 0.5),
                          (int) head->max / 60);

        if (head->max_stale >= 0)
            storeAppendPrintf(entry, " max-stale=%d", head->max_stale);

        if (head->flags.refresh_ims)
            storeAppendPrintf(entry, " refresh-ims");

        if (head->flags.store_stale)
            storeAppendPrintf(entry, " store-stale");

#if USE_HTTP_VIOLATIONS

        if (head->flags.override_expire)
            storeAppendPrintf(entry, " override-expire");

        if (head->flags.override_lastmod)
            storeAppendPrintf(entry, " override-lastmod");

        if (head->flags.reload_into_ims)
            storeAppendPrintf(entry, " reload-into-ims");

        if (head->flags.ignore_reload)
            storeAppendPrintf(entry, " ignore-reload");

        if (head->flags.ignore_no_store)
            storeAppendPrintf(entry, " ignore-no-store");

        if (head->flags.ignore_private)
            storeAppendPrintf(entry, " ignore-private");
#endif

        storeAppendPrintf(entry, "\n");

        head = head->next;
    }
}