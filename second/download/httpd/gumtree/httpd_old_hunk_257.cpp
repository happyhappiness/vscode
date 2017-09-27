        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s", errmsg);
        exit(1);
    }

    ap_cfg_closefile(cfp);
}

AP_DECLARE(void) ap_process_config_tree(server_rec *s,
                                        ap_directive_t *conftree,
                                        apr_pool_t *p, apr_pool_t *ptemp)
{
