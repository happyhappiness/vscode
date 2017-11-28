void
storeDirSwapLog(const StoreEntry * e, int op)
{
    assert (e);
    assert(!EBIT_TEST(e->flags, KEY_PRIVATE));
    assert(e->swap_filen >= 0);
    /*
     * icons and such; don't write them to the swap log
     */

    if (EBIT_TEST(e->flags, ENTRY_SPECIAL))
        return;

    assert(op > SWAP_LOG_NOP && op < SWAP_LOG_MAX);

    debugs(20, 3, "storeDirSwapLog: " <<
           swap_log_op_str[op] << " " <<
           e->getMD5Text() << " " <<
           e->swap_dirn << " " <<
           std::hex << std::uppercase << std::setfill('0') << std::setw(8) << e->swap_filen);

    dynamic_cast<SwapDir *>(INDEXSD(e->swap_dirn))->logEntry(*e, op);
}