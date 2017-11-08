static apr_status_t socache_dc_init(ap_socache_instance_t *ctx,
                                    const char *namespace,
                                    const struct ap_socache_hints *hints,
                                    server_rec *s, apr_pool_t *p)
{
#if 0
    /* If a "persistent connection" mode of operation is preferred, you *must*
     * also use the PIDCHECK flag to ensure fork()'d processes don't interlace
     * comms on the same connection as each other. */
#define SESSION_CTX_FLAGS        SESSION_CTX_FLAG_PERSISTENT | \
                                 SESSION_CTX_FLAG_PERSISTENT_PIDCHECK | \
                                 SESSION_CTX_FLAG_PERSISTENT_RETRY | \
                                 SESSION_CTX_FLAG_PERSISTENT_LATE
#else
    /* This mode of operation will open a temporary connection to the 'target'
     * for each cache operation - this makes it safe against fork()
     * automatically. This mode is preferred when running a local proxy (over
     * unix domain sockets) because overhead is negligable and it reduces the
     * performance/stability danger of file-descriptor bloatage. */
#define SESSION_CTX_FLAGS        0
#endif
    ctx->dc = DC_CTX_new(ctx->target, SESSION_CTX_FLAGS);
    if (!ctx->dc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00738) "distributed scache failed to obtain context");
        return APR_EGENERAL;
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(00739) "distributed scache context initialised");

    return APR_SUCCESS;
}