
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "%s compiled against Server: %s, Library: %s",
                 modver, AP_SERVER_BASEVERSION, incver);
}

/*
 *  Per-module initialization
 */
int ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
                    apr_pool_t *ptemp,
                    server_rec *base_server)
