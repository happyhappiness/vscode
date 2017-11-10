static void uldap_connection_close(util_ldap_connection_t *ldc)
{

     /* We leave bound LDAP connections floating around in our pool,
      * but always check/fix the binddn/bindpw when we take them out
      * of the pool
      */
     if (!ldc->keep) {
         uldap_connection_unbind(ldc);
         ldc->r = NULL;
     }
     else {
         /* mark our connection as available for reuse */
         ldc->freed = apr_time_now();
         ldc->r = NULL;
     }

#if APR_HAS_THREADS
     apr_thread_mutex_unlock(ldc->lock);
#endif
}