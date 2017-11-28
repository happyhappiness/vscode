void
StoreEntry::makePrivate()
{
    /* This object should never be cached at all */
    expireNow();
    releaseRequest(); /* delete object when not used */
    /* releaseRequest clears ENTRY_CACHABLE flag */
}