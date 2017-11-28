static void
authenticateDigestNonceSetup(void)
{
    if (!digest_nonce_pool)
        digest_nonce_pool = memPoolCreate("Digest Scheme nonce's", sizeof(digest_nonce_h));

    if (!digest_nonce_cache) {
        digest_nonce_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);
        assert(digest_nonce_cache);
        eventAdd("Digest none cache maintenance", authenticateDigestNonceCacheCleanup, NULL, digestConfig.nonceGCInterval, 1);
    }
}