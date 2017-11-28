void
FtpStateData::haveParsedReplyHeaders()
{
    ServerStateData::haveParsedReplyHeaders();

    StoreEntry *e = entry;

    e->timestampsSet();

    if (flags.authenticated) {
        /*
         * Authenticated requests can't be cached.
         */
        e->release();
    } else if (EBIT_TEST(e->flags, ENTRY_CACHABLE) && !getCurrentOffset()) {
        e->setPublicKey();
    } else {
        e->release();
    }
}