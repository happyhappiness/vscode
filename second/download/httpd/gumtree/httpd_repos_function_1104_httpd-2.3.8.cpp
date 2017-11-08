static apr_status_t socache_dbm_init(ap_socache_instance_t *ctx, 
                                     const char *namespace, 
                                     const struct ap_socache_hints *hints,
                                     server_rec *s, apr_pool_t *p)
{
    apr_dbm_t *dbm;
    apr_status_t rv;

    /* for the DBM we need the data file */
    if (ctx->data_file == NULL) {
        const char *path = apr_pstrcat(p, DEFAULT_DBM_PREFIX, namespace,
                                       NULL);

        ctx->data_file = ap_server_root_relative(p, path);

        if (ctx->data_file == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "could not use default path '%s' for DBM socache",
                         path);
            return APR_EINVAL;
        }
    }

    /* open it once to create it and to make sure it _can_ be created */
    apr_pool_clear(ctx->pool);

    if ((rv = apr_dbm_open(&dbm, ctx->data_file,
            APR_DBM_RWCREATE, DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create socache DBM file `%s'",
                     ctx->data_file);
        return rv;
    }
    apr_dbm_close(dbm);

    ctx->expiry_interval = (hints && hints->expiry_interval 
                            ? hints->expiry_interval : apr_time_from_sec(30));

#if AP_NEED_SET_MUTEX_PERMS
    /*
     * We have to make sure the Apache child processes have access to
     * the DBM file. But because there are brain-dead platforms where we
     * cannot exactly determine the suffixes we try all possibilities.
     */
    if (geteuid() == 0 /* is superuser */) {
        chown(ctx->data_file, ap_unixd_config.user_id, -1 /* no gid change */);
        if (chown(apr_pstrcat(p, ctx->data_file, DBM_FILE_SUFFIX_DIR, NULL),
                  ap_unixd_config.user_id, -1) == -1) {
            if (chown(apr_pstrcat(p, ctx->data_file, ".db", NULL),
                      ap_unixd_config.user_id, -1) == -1)
                chown(apr_pstrcat(p, ctx->data_file, ".dir", NULL),
                      ap_unixd_config.user_id, -1);
        }
        if (chown(apr_pstrcat(p, ctx->data_file, DBM_FILE_SUFFIX_PAG, NULL),
                  ap_unixd_config.user_id, -1) == -1) {
            if (chown(apr_pstrcat(p, ctx->data_file, ".db", NULL),
                      ap_unixd_config.user_id, -1) == -1)
                chown(apr_pstrcat(p, ctx->data_file, ".pag", NULL),
                      ap_unixd_config.user_id, -1);
        }
    }
#endif
    socache_dbm_expire(ctx, s);

    return APR_SUCCESS;
}