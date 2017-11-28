void
Ftp::Gateway::haveParsedReplyHeaders()
{
    Client::haveParsedReplyHeaders();

    StoreEntry *e = entry;

    e->timestampsSet();

    if (flags.authenticated) {
        /*
         * Authenticated requests can't be cached.
         */
        e->release();
    } else if (!EBIT_TEST(e->flags, RELEASE_REQUEST) && !getCurrentOffset()) {
        e->setPublicKey();
    } else {
        e->release();
    }
}