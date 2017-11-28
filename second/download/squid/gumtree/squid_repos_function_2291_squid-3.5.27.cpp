void
storeDigestNoteStoreReady(void)
{
#if USE_CACHE_DIGESTS

    if (Config.onoff.digest_generation) {
        storeDigestRebuildStart(NULL);
        storeDigestRewriteStart(NULL);
    }

#endif
}