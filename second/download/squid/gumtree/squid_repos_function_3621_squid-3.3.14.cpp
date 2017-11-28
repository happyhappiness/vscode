int
refreshCheckDigest(const StoreEntry * entry, time_t delta)
{
    int reason = refreshCheck(entry,
                              entry->mem_obj ? entry->mem_obj->request : NULL,
                              delta);
    ++ refreshCounts[rcCDigest].total;
    ++ refreshCounts[rcCDigest].status[reason];
    return (reason < 200) ? 0 : 1;
}