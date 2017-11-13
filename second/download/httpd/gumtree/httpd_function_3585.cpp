static void dbd_child_init(apr_pool_t *p, server_rec *s)
{
  apr_status_t rv = dbd_setup_init(p, s);
  if (rv) {
    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                 "DBD: child init failed!");
  }
}