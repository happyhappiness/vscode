void
authenticateDigestNonceShutdown(void)
{
    /*
     * We empty the cache of any nonces left in there.
     */
    digest_nonce_h *nonce;

    if (digest_nonce_cache) {
        debugs(29, 2, "authenticateDigestNonceShutdown: Shutting down nonce cache ");
        hash_first(digest_nonce_cache);

        while ((nonce = ((digest_nonce_h *) hash_next(digest_nonce_cache)))) {
            assert(nonce->flags.incache);
            authDigestNoncePurge(nonce);
        }
    }

#if DEBUGSHUTDOWN
    if (digest_nonce_pool) {
        delete digest_nonce_pool;
        digest_nonce_pool = NULL;
    }

#endif
    debugs(29, 2, "authenticateDigestNonceShutdown: Nonce cache shutdown");
}