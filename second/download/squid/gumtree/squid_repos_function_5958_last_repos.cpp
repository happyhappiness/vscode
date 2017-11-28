static void
authenticateDigestNonceSetup(void)
{
    if (!digest_nonce_pool)
        digest_nonce_pool = memPoolCreate("Digest Scheme nonce's", sizeof(digest_nonce_h));

    if (!digest_nonce_cache) {
        digest_nonce_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);
        assert(digest_nonce_cache);
        eventAdd("Digest nonce cache maintenance", authenticateDigestNonceCacheCleanup, NULL, static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->nonceGCInterval, 1);
    }
}