void ssl_scache_dc_init(server_rec *s, apr_pool_t *p)
{
    DC_CTX *ctx;
    SSLModConfigRec *mc = myModConfig(s);
    /*
     * Create a session context
     */
    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "SSLSessionCache required");
        ssl_die();
    }
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
    ctx = DC_CTX_new(mc->szSessionCacheDataFile, SESSION_CTX_FLAGS);
    if (!ctx) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache failed to obtain context");
        ssl_die();
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, "distributed scache context initialised");
    /*
     * Success ...
     */
    mc->tSessionCacheDataTable = ctx;
    return;
}