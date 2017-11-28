int
StoreEntry::unlock()
{
    --lock_count;
    debugs(20, 3, "StoreEntry::unlock: key '" << getMD5Text() << "' count=" << lock_count);

    if (lock_count)
        return (int) lock_count;

    if (store_status == STORE_PENDING)
        setReleaseFlag();

    assert(storePendingNClients(this) == 0);

    if (EBIT_TEST(flags, RELEASE_REQUEST)) {
        this->release();
        return 0;
    }

    if (EBIT_TEST(flags, KEY_PRIVATE))
        debugs(20, DBG_IMPORTANT, "WARNING: " << __FILE__ << ":" << __LINE__ << ": found KEY_PRIVATE");

    Store::Root().handleIdleEntry(*this); // may delete us
    return 0;
}