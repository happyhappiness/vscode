    util_dn_compare_node_t *node = (util_dn_compare_node_t *)n;
    util_ald_free(cache, node->reqdn);
    util_ald_free(cache, node->dn);
    util_ald_free(cache, node);
}

void util_ldap_dn_compare_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_dn_compare_node_t *node = (util_dn_compare_node_t *)n;
    char *buf;

    buf = apr_psprintf(r->pool, 
             "<tr valign='top'>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<tr>",
         node->reqdn,
         node->dn);

    ap_rputs(buf, r);
}


/* ------------------------------------------------------------------ */
apr_status_t util_ldap_cache_child_kill(void *data);
apr_status_t util_ldap_cache_module_kill(void *data);

apr_status_t util_ldap_cache_module_kill(void *data)
{
    util_ldap_state_t *st = (util_ldap_state_t *)data;

    util_ald_destroy_cache(st->util_ldap_cache);
#if APR_HAS_SHARED_MEMORY
    if (st->cache_rmm != NULL) {
        apr_rmm_destroy (st->cache_rmm);
        st->cache_rmm = NULL;
    }
    if (st->cache_shm != NULL) {
        apr_status_t result = apr_shm_destroy(st->cache_shm);
        st->cache_shm = NULL;
        apr_file_remove(st->cache_file, st->pool);
        return result;
    }
#endif
    return APR_SUCCESS;
}

apr_status_t util_ldap_cache_init(apr_pool_t *pool, util_ldap_state_t *st)
{
#if APR_HAS_SHARED_MEMORY
    apr_status_t result;

    result = apr_shm_create(&st->cache_shm, st->cache_bytes, st->cache_file, st->pool);
    if (result == APR_EEXIST) {
        /*
         * The cache could have already been created (i.e. we may be a child process).  See
         * if we can attach to the existing shared memory
         */
        result = apr_shm_attach(&st->cache_shm, st->cache_file, st->pool);
    } 
