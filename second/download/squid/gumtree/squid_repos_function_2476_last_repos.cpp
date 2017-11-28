void
StoreEntry::releaseRequest(const bool shareable)
{
    if (EBIT_TEST(flags, RELEASE_REQUEST))
        return;

    setReleaseFlag(); // makes validToSend() false, preventing future hits

    setPrivateKey(shareable);
}