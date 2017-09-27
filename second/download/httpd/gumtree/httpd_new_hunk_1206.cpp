#endif
    }

    return rv;
}

static void dbd_child_init(apr_pool_t *p, server_rec *s)
{
  apr_status_t rv = dbd_setup_init(p, s);
  if (rv) {
    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                 "DBD: child init failed!");
  }
}

#if APR_HAS_THREADS
static apr_status_t dbd_setup_lock(server_rec *s, dbd_group_t *group)
{
    apr_status_t rv = APR_SUCCESS, rv2;

    /* several threads could be here at the same time, all trying to
