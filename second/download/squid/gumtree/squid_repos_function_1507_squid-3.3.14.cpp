bool
SwapDir::canLog(StoreEntry const &e)const
{
    if (e.swap_filen < 0)
        return false;

    if (e.swap_status != SWAPOUT_DONE)
        return false;

    if (e.swap_file_sz <= 0)
        return false;

    if (EBIT_TEST(e.flags, RELEASE_REQUEST))
        return false;

    if (EBIT_TEST(e.flags, KEY_PRIVATE))
        return false;

    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
        return false;

    return true;
}