bool
clientReplyContext::errorInStream(StoreIOBuffer const &result, size_t const &sizeToProcess)const
{
    return /* aborted request */
        (http->storeEntry() && EBIT_TEST(http->storeEntry()->flags, ENTRY_ABORTED)) ||
        /* Upstream read error */ (result.flags.error) ||
        /* Upstream EOF */ (sizeToProcess == 0);
}