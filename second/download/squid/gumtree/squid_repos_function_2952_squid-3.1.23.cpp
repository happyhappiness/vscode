void
StoreEntry::releaseRequest()
{
    if (EBIT_TEST(flags, RELEASE_REQUEST))
        return;

    setReleaseFlag();

    /*
     * Clear cachable flag here because we might get called before
     * anyone else even looks at the cachability flag.  Also, this
     * prevents httpMakePublic from really setting a public key.
     */
    EBIT_CLR(flags, ENTRY_CACHABLE);

    setPrivateKey();
}