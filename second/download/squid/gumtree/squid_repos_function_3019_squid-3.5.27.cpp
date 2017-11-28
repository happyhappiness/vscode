void
StoreEntry::makePrivate(const bool shareable)
{
    /* This object should never be cached at all */
    expireNow();
    releaseRequest(shareable); /* delete object when not used */
}