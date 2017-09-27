
    apr_pool_create(&ctx->pool, p);

    return NULL;
}

#if AP_NEED_SET_MUTEX_PERMS
static int try_chown(apr_pool_t *p, server_rec *s,
                     const char *name, const char *suffix)
{
    if (suffix)
        name = apr_pstrcat(p, name, suffix, NULL);
    if (-1 == chown(name, ap_unixd_config.user_id,
                    (gid_t)-1 /* no gid change */ ))
    {
        if (errno != ENOENT)
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(errno), s, APLOGNO(00802)
                         "Can't change owner of %s", name);
        return -1;
    }
    return 0;
}
#endif


static apr_status_t socache_dbm_init(ap_socache_instance_t *ctx,
                                     const char *namespace,
                                     const struct ap_socache_hints *hints,
                                     server_rec *s, apr_pool_t *p)
{
    apr_dbm_t *dbm;
    apr_status_t rv;

