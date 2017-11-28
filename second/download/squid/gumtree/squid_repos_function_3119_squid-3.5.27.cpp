bool
StoreEntry::isAccepting() const
{
    if (STORE_PENDING != store_status)
        return false;

    if (EBIT_TEST(flags, ENTRY_ABORTED))
        return false;

    return true;
}