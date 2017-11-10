static walk_cache_t *prep_walk_cache(apr_size_t t, request_rec *r)
{
    walk_cache_t *cache;
    void **note;

    /* Find the most relevant, recent entry to work from.  That would be
     * this request (on the second call), or the parent request of a
     * subrequest, or the prior request of an internal redirect.  Provide
     * this _walk()er with a copy it is allowed to munge.  If there is no
     * parent or prior cached request, then create a new walk cache.
     */
    note = ap_get_request_note(r, t);
    if (!note) {
        return NULL;
    }

    if (!(cache = *note)) {
        void **inherit_note;

        if ((r->main
             && ((inherit_note = ap_get_request_note(r->main, t)))
             && *inherit_note)
            || (r->prev
                && ((inherit_note = ap_get_request_note(r->prev, t)))
                && *inherit_note)) {
            cache = apr_pmemdup(r->pool, *inherit_note,
                                sizeof(*cache));
            cache->walked = apr_array_copy(r->pool, cache->walked);
        }
        else {
            cache = apr_pcalloc(r->pool, sizeof(*cache));
            cache->walked = apr_array_make(r->pool, 4, sizeof(walk_walked_t));
        }

        *note = cache;
    }
    return cache;
}