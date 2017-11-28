void
httpHeaderFieldStatDumper(StoreEntry * sentry, int, double val, double, int count)
{
    const int id = static_cast<int>(val);
    const bool valid_id = Http::any_valid_header(static_cast<Http::HdrType>(id));
    const char *name = valid_id ? Http::HeaderLookupTable.lookup(static_cast<Http::HdrType>(id)).name : "INVALID";
    int visible = count > 0;
    /* for entries with zero count, list only those that belong to current type of message */

    if (!visible && valid_id && dump_stat->owner_mask)
        visible = CBIT_TEST(*dump_stat->owner_mask, id);

    if (visible)
        storeAppendPrintf(sentry, "%2d\t %-20s\t %5d\t %6.2f\n",
                          id, name, count, xdiv(count, dump_stat->busyDestroyedCount));
}