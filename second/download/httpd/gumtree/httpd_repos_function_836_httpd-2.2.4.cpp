void ssl_scache_dc_status(request_rec *r, int flags, apr_pool_t *pool)
{
    SSLModConfigRec *mc = myModConfig(r->server);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "distributed scache 'ssl_scache_dc_status'");
    ap_rprintf(r, "cache type: <b>DC (Distributed Cache)</b>, "
               " target: <b>%s</b><br>", mc->szSessionCacheDataFile);
}