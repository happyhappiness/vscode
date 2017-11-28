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
