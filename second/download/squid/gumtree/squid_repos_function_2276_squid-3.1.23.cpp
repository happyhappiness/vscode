static void
CheckQuickAbort(StoreEntry * entry)
{
    assert (entry);

    if (storePendingNClients(entry) > 0)
        return;

    if (entry->store_status != STORE_PENDING)
        return;

    if (EBIT_TEST(entry->flags, ENTRY_SPECIAL))
        return;

    if (CheckQuickAbort2(entry) == 0)
        return;

    entry->abort();
}