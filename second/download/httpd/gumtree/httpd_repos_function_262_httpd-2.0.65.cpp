static void dav_register_liveprop_namespace(apr_pool_t *p, const char *uri)
{
    int value;

    if (dav_liveprop_uris == NULL) {
        dav_liveprop_uris = apr_hash_make(p);
        apr_pool_cleanup_register(p, NULL, dav_cleanup_liveprops, apr_pool_cleanup_null);
    }

    value = (int)apr_hash_get(dav_liveprop_uris, uri, APR_HASH_KEY_STRING);
    if (value != 0) {
        /* already registered */
        return;
    }

    /* start at 1, and count up */
    apr_hash_set(dav_liveprop_uris, uri, APR_HASH_KEY_STRING,
                 (void *)++dav_liveprop_count);
}