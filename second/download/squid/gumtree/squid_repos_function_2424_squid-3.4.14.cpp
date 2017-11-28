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

    if (!CheckQuickAbortIsReasonable(entry))
        return;

    entry->abort();
}