        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "LDAP: SSL support unavailable%s%s",
                     result_err ? ": " : "",
                     result_err ? result_err->reason : "");
    }

    return(OK);
}

static void util_ldap_child_init(apr_pool_t *p, server_rec *s)
{
    apr_status_t sts;
    util_ldap_state_t *st = ap_get_module_config(s->module_config,
                                                 &ldap_module);

    if (!st->util_ldap_cache_lock) return;

    sts = apr_global_mutex_child_init(&st->util_ldap_cache_lock,
                                      st->lock_file, p);
    if (sts != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s,
                     "Failed to initialise global mutex %s in child process %"
                     APR_PID_T_FMT ".",
                     st->lock_file, getpid());
    }
}

static const command_rec util_ldap_cmds[] = {
    AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes,
                  NULL, RSRC_CONF,
