int
StoreEntry::locked() const
{
    if (lock_count)
        return 1;

    /*
     * SPECIAL, PUBLIC entries should be "locked";
     * XXX: Their owner should lock them then instead of relying on this hack.
     */
    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        if (!EBIT_TEST(flags, KEY_PRIVATE))
            return 1;

    return 0;
}