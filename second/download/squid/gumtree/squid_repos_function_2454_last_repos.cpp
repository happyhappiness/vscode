void
StoreEntry::makePublic(const KeyScope scope)
{
    /* This object can be cached for a long time */
    if (!EBIT_TEST(flags, RELEASE_REQUEST))
        setPublicKey(scope);
}