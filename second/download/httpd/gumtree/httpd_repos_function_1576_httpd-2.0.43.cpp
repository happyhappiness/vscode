void util_ldap_connection_close(util_ldap_connection_t *ldc)
{

    /*
     * QUESTION:
     *
     * Is it safe leaving bound connections floating around between the
     * different modules? Keeping the user bound is a performance boost,
     * but it is also a potential security problem - maybe.
     *
     * For now we unbind the user when we finish with a connection, but
     * we don't have to...
     */

    /* mark our connection as available for reuse */

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(ldc->lock);
#endif
}