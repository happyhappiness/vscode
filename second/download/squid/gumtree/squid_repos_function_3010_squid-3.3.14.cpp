int
StoreEntry::locked() const
{
    if (lock_count)
        return 1;

    if (swap_status == SWAPOUT_WRITING)
        return 1;

    if (store_status == STORE_PENDING)
        return 1;

    /*
     * SPECIAL, PUBLIC entries should be "locked"
     */
    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        if (!EBIT_TEST(flags, KEY_PRIVATE))
            return 1;

    return 0;
}