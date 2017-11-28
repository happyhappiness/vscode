static void
authenticateDigestNonceCacheCleanup(void *data)
{
    /*
     * We walk the hash by nonceb64 as that is the unique key we
     * use.  For big hash tables we could consider stepping through
     * the cache, 100/200 entries at a time. Lets see how it flies
     * first.
     */
    digest_nonce_h *nonce;
    debugs(29, 3, "Cleaning the nonce cache now");
    debugs(29, 3, "Current time: " << current_time.tv_sec);
    hash_first(digest_nonce_cache);

    while ((nonce = ((digest_nonce_h *) hash_next(digest_nonce_cache)))) {
        debugs(29, 3, "nonce entry  : " << nonce << " '" << (char *) nonce->key << "'");
        debugs(29, 4, "Creation time: " << nonce->noncedata.creationtime);

        if (authDigestNonceIsStale(nonce)) {
            debugs(29, 4, "Removing nonce " << (char *) nonce->key << " from cache due to timeout.");
            assert(nonce->flags.incache);
            /* invalidate nonce so future requests fail */
            nonce->flags.valid = false;
            /* if it is tied to a auth_user, remove the tie */
            authDigestNonceUserUnlink(nonce);
            authDigestNoncePurge(nonce);
        }
    }

    debugs(29, 3, "Finished cleaning the nonce cache.");

    if (static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->active())
        eventAdd("Digest nonce cache maintenance", authenticateDigestNonceCacheCleanup, NULL, static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->nonceGCInterval, 1);
}