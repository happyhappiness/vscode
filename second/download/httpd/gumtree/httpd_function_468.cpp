static void util_ldap_child_init(apr_pool_t *p, server_rec *s)
{
    apr_status_t sts;
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(s->module_config, &ldap_module);

    sts = apr_global_mutex_child_init(&st->util_ldap_cache_lock, st->lock_file, p);
    if (sts != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s, "failed to init caching lock in child process");
        return;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, s, 
                     "INIT global mutex %s in child %d ", st->lock_file, getpid());
    }
}