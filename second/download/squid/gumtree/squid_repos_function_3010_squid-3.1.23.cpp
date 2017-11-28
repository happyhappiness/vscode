bool
StoreEntry::swapoutPossible()
{
    /* should we swap something out to disk? */
    debugs(20, 7, "storeSwapOut: " << url());
    debugs(20, 7, "storeSwapOut: store_status = " << storeStatusStr[store_status]);

    if (EBIT_TEST(flags, ENTRY_ABORTED)) {
        assert(EBIT_TEST(flags, RELEASE_REQUEST));
        swapOutFileClose();
        return false;
    }

    if (EBIT_TEST(flags, ENTRY_SPECIAL)) {
        debugs(20, 3, "storeSwapOut: " << url() << " SPECIAL");
        return false;
    }

    return true;
}