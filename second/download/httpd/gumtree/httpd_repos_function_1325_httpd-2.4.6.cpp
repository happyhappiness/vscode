static apr_status_t socache_shmcb_iterate(ap_socache_instance_t *instance,
                                          server_rec *s, void *userctx,
                                          ap_socache_iterator_t *iterator,
                                          apr_pool_t *pool)
{
    SHMCBHeader *header = instance->header;
    unsigned int loop;
    apr_time_t now = apr_time_now();
    apr_status_t rv = APR_SUCCESS;
    apr_size_t buflen = 0;
    unsigned char *buf = NULL;

    /* Perform the iteration inside the mutex to avoid corruption or invalid
     * pointer arithmetic. The rest of our logic uses read-only header data so
     * doesn't need the lock. */
    /* Iterate over the subcaches */
    for (loop = 0; loop < header->subcache_num && rv == APR_SUCCESS; loop++) {
        SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
        rv = shmcb_subcache_iterate(instance, s, userctx, header, subcache,
                                    iterator, &buf, &buflen, pool, now);
    }
    return rv;
}