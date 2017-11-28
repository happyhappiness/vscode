int
StoreEntry::unlock()
{
    lock_count--;
    debugs(20, 3, "StoreEntry::unlock: key '" << getMD5Text() << "' count=" << lock_count);

    if (lock_count)
        return (int) lock_count;

    if (store_status == STORE_PENDING)
        setReleaseFlag();

    assert(storePendingNClients(this) == 0);

    if (EBIT_TEST(flags, RELEASE_REQUEST))
        this->release();
    else if (keepInMemory()) {
        Store::Root().dereference(*this);
        setMemStatus(IN_MEMORY);
        mem_obj->unlinkRequest();
    } else {
        Store::Root().dereference(*this);

        if (EBIT_TEST(flags, KEY_PRIVATE))
            debugs(20, 1, "WARNING: " << __FILE__ << ":" << __LINE__ << ": found KEY_PRIVATE");

        /* StoreEntry::purgeMem may free e */
        purgeMem();
    }

    return 0;
}