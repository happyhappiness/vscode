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

command_rec util_ldap_cmds[] = {
    AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes, NULL, RSRC_CONF,
                  "Sets the size of the shared memory cache in bytes. "
