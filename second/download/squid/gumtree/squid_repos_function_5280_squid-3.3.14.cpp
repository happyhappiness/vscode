static void
authenticateDigestNonceDelete(digest_nonce_h * nonce)
{
    if (nonce) {
        assert(nonce->references == 0);
#if UNREACHABLECODE

        if (nonce->flags.incache)
            hash_remove_link(digest_nonce_cache, nonce);

#endif

        assert(nonce->flags.incache == 0);

        safe_free(nonce->key);

        digest_nonce_pool->freeOne(nonce);
    }
}