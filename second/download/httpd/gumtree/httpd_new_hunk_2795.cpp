    /* If no connection was found after the second search, we
     * must create one.
     */
    if (!l) {
        apr_pool_t *newpool;
        if (apr_pool_create(&newpool, NULL) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01285)
                          "util_ldap: Failed to create memory pool");
#if APR_HAS_THREADS
            apr_thread_mutex_unlock(st->mutex);
#endif
            return NULL;
        }

        /*
         * Add the new connection entry to the linked list. Note that we
         * don't actually establish an LDAP connection yet; that happens
         * the first time authentication is requested.
         */

