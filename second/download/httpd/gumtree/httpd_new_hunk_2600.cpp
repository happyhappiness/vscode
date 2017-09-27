        /* we failed, so create a mutex so that subsequent competing callers
         * to ap_dbd_open can serialize themselves while they retry
         */
        rv2 = apr_thread_mutex_create(&group->mutex,
                                      APR_THREAD_MUTEX_DEFAULT, pool);
        if (rv2 != APR_SUCCESS) {
             ap_log_error(APLOG_MARK, APLOG_CRIT, rv2, s, APLOGNO(00635)
                          "Failed to create thread mutex");
             return rv2;
        }
#endif
    }

    return rv;
}

static void dbd_child_init(apr_pool_t *p, server_rec *s)
{
  apr_status_t rv = dbd_setup_init(p, s);
  if (rv) {
    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00636)
                 "child init failed!");
  }
}

#if APR_HAS_THREADS
static apr_status_t dbd_setup_lock(server_rec *s, dbd_group_t *group)
{
