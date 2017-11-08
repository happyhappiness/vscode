static apr_status_t util_ldap_connection_remove (void *param) { 
    util_ldap_connection_t *ldc = param, *l  = NULL, *prev = NULL;
    util_ldap_state_t *st;

    if (!ldc) return APR_SUCCESS;

    st = ldc->st;

    uldap_connection_unbind(ldc);

#if APR_HAS_THREADS
    apr_thread_mutex_lock(st->mutex);
#endif

    /* Remove ldc from the list */
    for (l=st->connections; l; l=l->next) {
        if (l == ldc) {
            if (prev) {
                prev->next = l->next; 
            }
            else { 
                st->connections = l->next;
            }
            break;
        }
        prev = l;
    }

    /* Some unfortunate duplication between this method
     * and uldap_connection_cleanup()
    */
    if (ldc->bindpw) {
        free((void*)ldc->bindpw);
    }
    if (ldc->binddn) {
        free((void*)ldc->binddn);
    }

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(ldc->lock);
    apr_thread_mutex_unlock(st->mutex);
#endif

    /* Destory the pool associated with this connection */

    apr_pool_destroy(ldc->pool);   
   
    return APR_SUCCESS;
}