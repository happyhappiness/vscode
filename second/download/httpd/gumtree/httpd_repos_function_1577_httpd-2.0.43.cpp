apr_status_t util_ldap_connection_destroy(void *param)
{
    util_ldap_connection_t *ldc = param;

    /* unbinding from the LDAP server */
    if (ldc->ldap) {
        ldap_unbind_s(ldc->ldap);
        ldc->bound = 0;
        ldc->ldap = NULL;
    }

    /* release the lock we were using.  The lock should have
       already been released in the close connection call.  
       But just in case it wasn't, we first try to get the lock
       before unlocking it to avoid unlocking an unheld lock. 
       Unlocking an unheld lock causes problems on NetWare.  The
       other option would be to assume that close connection did
       its job. */
#if APR_HAS_THREADS
    apr_thread_mutex_trylock(ldc->lock);
    apr_thread_mutex_unlock(ldc->lock);
#endif

    return APR_SUCCESS;
}